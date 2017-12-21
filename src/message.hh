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

private:
    Chunk();
    Chunk(std::string message);
    void init();
    size_t indexToBigEndianIndex(size_t);
    uint8_t data[64];
};

class Schedule {
public:
    Schedule(const Chunk &);
    Schedule(const Schedule &);
    ~Schedule() {}
    const uint32_t *wordPtr() const;

private:
    void copyChunk(const Chunk &);
    void extendRest();
    uint32_t data[64];
};

}
}
