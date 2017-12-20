#pragma once

#include "message.hh"
#include <vector>

namespace sha {

class Hash
{
public:
    Hash();
    void round(const sha::Message::Schedule &);
    void round(const std::vector<sha::Message::Chunk> &);
    const uint32_t *get() const;

private:
    uint32_t calculateT1(size_t, const uint32_t *, const uint32_t *) const;
    uint32_t calculateT2(const uint32_t *) const;
    void loopRounds(uint32_t *, const uint32_t *);
    void rotateOld(uint32_t *r);
    void applyTemp(uint32_t *r, uint32_t, uint32_t);
    void appendRound(const uint32_t *);

    uint32_t hash[8];
};

}
