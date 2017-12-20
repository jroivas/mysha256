#include "message.hh"

#include <string.h>
#include <math.h>
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
        //data[i] = message[i];
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
    data = new uint8_t[64]();
    //data[64] = 0x80;
}

const uint32_t *Chunk::wordPtr() const
{
    return reinterpret_cast<uint32_t*>(data);
}

void Chunk::insertLength(size_t length)
{
    uint64_t lenvar = (length - 1) * 8;
    uint32_t *tmp = reinterpret_cast<uint32_t*>(data);
    tmp[14] = (lenvar >> 32) & 0xFFFFFFFF;
    tmp[15] = lenvar & 0xFFFFFFFF;
}

Schedule::Schedule(const Chunk &chunk)
{
    data = new uint32_t[64];
    copyChunk(chunk);
    extendRest();
}

Schedule::Schedule(const Schedule &other)
{
    data = new uint32_t[64];
    for (size_t i = 0; i < 64; ++i) data[i] = other.data[i];
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

std::vector<Chunk> sha::Message::Chunk::create(const std::string message)
{
    std::string data = message;
    data += 0x80;
    std::vector<Chunk> res;
    size_t len = data.length();
    size_t len1 = len / 4 + 2;
    size_t chunks = ceil(len1 / 16.0);
    for (size_t i = 0; i < chunks; ++i) {
        std::string d = "";
        if (i * 64 < len) d = data.substr(i * 64);
        Chunk a(d);
        if (i == chunks - 1) a.insertLength(len);
        res.push_back(a);
    }
    /*
    while (data.length() > 0) {
        Chunk a(data);
        res.push_back(a);
        data = data.length() > 64 ? data.substr(64) : "";
    }
    */
    return res;
}

