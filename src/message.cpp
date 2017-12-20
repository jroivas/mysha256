#include "message.hh"

#include <string.h>
#include "boxes.hh"

using sha::Message::Chunk;
using sha::Message::Schedule;

Chunk::Chunk()
{
    init();
}

Chunk::Chunk(std::string message)
{
    init();
    size_t l = message.length();
    if (l > 64) l  = 64;
    for (size_t i = 0; i < l; ++i) {
        data[indexToBigEndianIndex(i)] = message[i];
    }
}

Chunk::Chunk(const Chunk &other)
{
    init();
    memcpy(data, other.data, 65);
}

size_t Chunk::indexToBigEndianIndex(size_t i)
{
    size_t idx = i / 4;
    size_t sub = i % 4;
    return idx * 4 + (3 - sub);
}

void Chunk::init()
{
    data = new uint8_t[64 + 1]();
    data[64] = 0x80;
}

const uint32_t *Chunk::wordPtr() const
{
    return reinterpret_cast<uint32_t*>(data);
}

std::vector<Chunk> sha::Message::createChunks(const std::string message)
{
    std::string data = message;
    std::vector<Chunk> res;
    while (data.length() > 0) {
        Chunk a(data);
        res.push_back(a);
        data = data.length() > 64 ? data.substr(64) : "";
    }
    return res;
}

Schedule::Schedule(const Chunk &chunk)
{
    data = new uint32_t[64];
    copyChunk(chunk);
    extendRest();
}

void Schedule::copyChunk(const Chunk &chunk)
{
    const uint32_t *src = chunk.wordPtr();
    for (size_t i = 0; i < 16; ++i) data[i] = src[i];
}

void Schedule::extendRest()
{
    for (size_t i = 16; i < 64; ++i) {
        uint32_t s0 = sha::Box::I0(data[i - 15]);
        uint32_t s1 = sha::Box::I1(data[i - 2]);
        data[i] = data[i - 16] + s0 + data[i - 7] + s1;
    }
}

const uint32_t *Schedule::wordPtr() const
{
    return data;
}
