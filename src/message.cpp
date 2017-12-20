#include "message.hh"
#include <string.h>

using sha::Message::Chunk;

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

uint32_t *Chunk::wordPtr()
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
