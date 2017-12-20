#pragma once

#include <string>
#include <vector>

namespace sha {
namespace Message {

class Chunk {
public:
    Chunk();
    Chunk(std::string message);
    uint32_t *wordPtr();

private:
    void init();
    size_t indexToBigEndianIndex(size_t);
    uint8_t *data;
};

std::vector<Chunk> createChunks(const std::string);


}
}
