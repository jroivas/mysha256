#include "message.hh"

#include <string.h>
#include <math.h>
#include "boxes.hh"

using sha::Message::Chunk;

Chunk::Chunk()
{
    init();
}

Chunk::Chunk(const char *message, size_t l)
{
    init();
    if (l > 64) l = 64;
    for (size_t i = 0; i < l; ++i) {
        data[indexToBigEndianIndex(i)] = message[i];
    }
    extendRest();
}

Chunk::Chunk(const char *message, size_t l, size_t length)
{
    init();
    if (l > 64) l = 64;
    for (size_t i = 0; i < l; ++i) {
        data[indexToBigEndianIndex(i)] = message[i];
    }
    insertLength(length);
    extendRest();
}

size_t Chunk::indexToBigEndianIndex(size_t i)
{
    size_t idx = i / 4;
    size_t sub = i % 4;
    return idx * 4 + (3 - sub);
}

void Chunk::init()
{
    memset(data, 0, 64 * 4);
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

std::unique_ptr<Chunk> sha::Message::Chunk::createChunkFromMessage(size_t index, size_t numChunks, const std::string &message)
{
    size_t pos = index * 64;
    size_t l = message.length();
    if (index * 64 < l) {
        l -= index * 64;
    } else {
        l = 0;
    }

    if (isLastChunk(index, numChunks)) {
        std::unique_ptr<Chunk> res(new Chunk(message.c_str() + pos, l, message.length()));
        return res;
    }
    std::unique_ptr<Chunk> res(new Chunk(message.c_str() + pos, l));
    return res;
}

std::vector<std::unique_ptr<Chunk>> sha::Message::Chunk::createChunks(const std::string &data)
{
    size_t chunks = numChunks(data.length());
    std::vector<std::unique_ptr<Chunk>> res;
    for (size_t i = 0; i < chunks; ++i)
        res.push_back(std::move(createChunkFromMessage(i, chunks, data)));
    return res;
}

std::vector<std::unique_ptr<Chunk>> sha::Message::Chunk::create(const std::string message)
{
    std::string data = message;
    data += uint8_t(0x80);
    return createChunks(data);
}

void sha::Message::Chunk::extendRest()
{
    uint32_t *dataWord = reinterpret_cast<uint32_t*>(data);
    for (size_t i = 16; i < 64; ++i) {
        uint32_t s0 = sha::Box::I0(dataWord[i - 15]);
        uint32_t s1 = sha::Box::I1(dataWord[i - 2]);
        dataWord[i] = dataWord[i - 16] + s0 + dataWord[i - 7] + s1;
    }
}
