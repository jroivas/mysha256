#pragma once

#include <string>
#include <vector>
#include <memory>

namespace sha {
namespace Message {

class Chunk {
public:
    static std::vector<std::unique_ptr<Chunk>> create(const std::string);
    ~Chunk() {}
    const uint32_t *wordPtr() const;
    void insertLength(size_t length);

    static size_t numChunks(size_t messageLength);
    static bool isLastChunk(size_t index, size_t numChunks);
    static std::unique_ptr<Chunk> createChunkFromMessage(size_t index, size_t numChunks, const std::string &message);
    static std::vector<std::unique_ptr<Chunk>> createChunks(const std::string &);
    static size_t indexToBigEndianIndex(size_t);

private:
    Chunk();
    Chunk(const char *, size_t);
    Chunk(const char *, size_t, size_t);
    void init();
    void extendRest();
    uint8_t data[64 * 4];
};

}
}
