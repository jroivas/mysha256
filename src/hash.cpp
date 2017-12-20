#include "hash.hh"
#include "constants.hh"
#include "boxes.hh"
#include <string.h>

using sha::Hash;

Hash::Hash() {
    memcpy(hash, sha::H, 4 * 8);
}

const uint32_t *Hash::get() const
{
    return hash;
}

void Hash::round(const sha::Message::Schedule &schedule)
{
    uint32_t a = hash[0];
    uint32_t b = hash[1];
    uint32_t c = hash[2];
    uint32_t d = hash[3];
    uint32_t e = hash[4];
    uint32_t f = hash[5];
    uint32_t g = hash[6];
    uint32_t h = hash[7];

    for (size_t i = 0; i < 64; ++i) {
        uint32_t T1 = h + sha::Box::S1(e) + sha::Box::Ch(e, f, g) + sha::K[i] + schedule.wordPtr()[i];
        uint32_t T2 = sha::Box::S0(a) + sha::Box::Ma(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}
