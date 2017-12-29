#pragma once

#include "message.hh"
#include <array>
#include <memory>
#include <vector>

namespace sha {

class Hash
{
public:
    Hash();
    Hash(const std::string);
    void round(std::unique_ptr<sha::Message::Chunk>&);
    void round(std::vector<std::unique_ptr<sha::Message::Chunk>> &);
    void calculate(const std::string);
    const uint32_t *get() const;
    std::string digest();
    std::array<uint32_t, 8> rawDigest() const;
    void reset();

private:
    inline uint32_t calculateT1(size_t i, const uint32_t *r, const uint32_t *data) const;
    inline uint32_t calculateT2(const uint32_t *r) const;
    void loopRounds(uint32_t *, const uint32_t *);
    void rotateOld(uint32_t *r);
    void applyTemp(uint32_t *r, uint32_t, uint32_t);
    void appendRound(const uint32_t *);

    uint32_t hash[8];
    std::string storedDigest;
};

}
