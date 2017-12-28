#pragma once

#include <string>
#include <vector>

namespace sha {
namespace Message {

class Chunk {
public:
    static std::vector<Chunk> create(const std::string);
    Chunk(const Chunk&);
    ~Chunk() {}
    const uint32_t *wordPtr() const;
    void insertLength(size_t length);

    static size_t numChunks(size_t messageLength);
    static bool isLastChunk(size_t index, size_t numChunks);
    static Chunk createChunkFromMessage(size_t index, size_t numChunks, const std::string &message);
    static std::vector<Chunk> createChunks(const std::string &);
    static size_t indexToBigEndianIndex(size_t);

private:
    Chunk();
    Chunk(std::string message);
    void init();
    void extendRest();
    uint8_t data[64 * 4];
};

}
}
