#pragma once

#include <string>
#include <vector>

namespace sha {
namespace Message {

class Chunk {
public:
    Chunk();
    Chunk(std::string message);
    Chunk(const Chunk&);
    ~Chunk() {
        delete[] data;
    }
    const uint32_t *wordPtr() const;

private:
    void init();
    size_t indexToBigEndianIndex(size_t);
    uint8_t *data;
};

class Schedule {
public:
    Schedule(const Chunk &);
    ~Schedule() {
        delete[] data;
    }
    const uint32_t *wordPtr() const;

private:
    void copyChunk(const Chunk &);
    uint32_t *data;
};

std::vector<Chunk> createChunks(const std::string);


}
}
