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
    if (l > 64) l = 64;
    for (size_t i = 0; i < l; ++i) {
        data[indexToBigEndianIndex(i)] = message[i];
    }
}

Chunk::Chunk(const Chunk &other)
{
    memcpy(data, other.data, 64);
}

size_t Chunk::indexToBigEndianIndex(size_t i)
{
    size_t idx = i / 4;
    size_t sub = i % 4;
    return idx * 4 + (3 - sub);
}

void Chunk::init()
{
    memset(data, 0, 64);
}

const uint32_t *Chunk::wordPtr() const
{
    return reinterpret_cast<const uint32_t*>(data);
}

void Chunk::insertLength(size_t length)
{
    uint64_t lenvar = (length - 1) * 8;
    uint32_t *tmp = reinterpret_cast<uint32_t*>(data);
    tmp[14] = (lenvar >> 32) & 0xFFFFFFFF;
    tmp[15] = lenvar & 0xFFFFFFFF;
}

size_t sha::Message::Chunk::numChunks(size_t messageLength)
{
    size_t len = messageLength / 4 + 2;
    return ceil(len / 16.0);
}

bool sha::Message::Chunk::isLastChunk(size_t index, size_t numChunks)
{
    return (index >= numChunks - 1);
}

Chunk sha::Message::Chunk::createChunkFromMessage(size_t index, size_t numChunks, const std::string &message)
{
    std::string data = "";
    if (index * 64 < message.length()) data = message.substr(index * 64);
    Chunk chunk(data);
    if (isLastChunk(index, numChunks)) chunk.insertLength(message.length());
    return chunk;
}

std::vector<Chunk> sha::Message::Chunk::createChunks(const std::string &data)
{
    size_t chunks = numChunks(data.length());
    std::vector<Chunk> res;
    for (size_t i = 0; i < chunks; ++i)
        res.push_back(createChunkFromMessage(i, chunks, data));
    return res;
}

std::vector<Chunk> sha::Message::Chunk::create(const std::string message)
{
    std::string data = message;
    data += uint8_t(0x80);
    return createChunks(data);
}

Schedule::Schedule(const Chunk &chunk)
{
    copyChunk(chunk);
    extendRest();
}

Schedule::Schedule(const Schedule &other)
{
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
