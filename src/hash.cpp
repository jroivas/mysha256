#include "hash.hh"
#include "constants.hh"
#include "boxes.hh"
#include <string.h>
#include <sstream>
#include <iomanip>

using sha::Hash;

Hash::Hash() {
    reset();
}

Hash::Hash(const std::string h)
{
    calculate(h);
}

void Hash::reset()
{
    memcpy(hash, sha::H, 4 * 8);
}

const uint32_t *Hash::get() const
{
    return hash;
}

uint32_t Hash::calculateT1(size_t i, const uint32_t *r, const uint32_t *data) const
{
    return r[7] + sha::Box::S1(r[4]) + sha::Box::Ch(r[4], r[5], r[6]) + sha::K[i] + data[i];
}

uint32_t Hash::calculateT2(const uint32_t *r) const
{
    return sha::Box::S0(r[0]) + sha::Box::Ma(r[0], r[1], r[2]);
}

void Hash::rotateOld(uint32_t *r)
{
    r[7] = r[6];
    r[6] = r[5];
    r[5] = r[4];
    r[4] = r[3];
    r[3] = r[2];
    r[2] = r[1];
    r[1] = r[0];
}

void Hash::applyTemp(uint32_t *r, uint32_t a, uint32_t b)
{
    r[0] = a;
    r[4] = b;
}

void Hash::loopRounds(uint32_t *r, const uint32_t *data)
{
    for (size_t i = 0; i < 64; ++i) {
        uint32_t T1 = calculateT1(i, r, data);
        uint32_t T2 = calculateT2(r);
        uint32_t T3 = r[3] + T1;
        rotateOld(r);
        applyTemp(r, T1 + T2, T3);
    }
}

void Hash::appendRound(const uint32_t *r)
{
    for (size_t i = 0; i < 8; ++i) hash[i] += r[i];
}

void Hash::round(const sha::Message::Chunk &schedule)
{
    storedDigest = "";
    uint32_t r[8];
    memcpy(r, hash, 8 * 4);
    loopRounds(r, schedule.wordPtr());
    appendRound(r);
}

void Hash::round(const std::vector<sha::Message::Chunk> &chunks)
{
    for (auto chunk : chunks) round(chunk);
}

std::string Hash::digest()
{
    if (storedDigest.empty()) {
        std::stringstream s;
        s << std::hex;
        for (size_t i = 0; i < 8; ++i)
             s << std::setfill('0') << std::setw(8) << hash[i] ;
        s << std::dec;
        storedDigest = s.str();
    }
    return storedDigest;
}

std::array<uint32_t, 8> Hash::rawDigest() const
{
    std::array<uint32_t, 8> res;
    std::copy(std::begin(hash), std::end(hash), std::begin(res));
    return res;
}

void Hash::calculate(const std::string str)
{
    reset();
    round(sha::Message::Chunk::create(str));
}
