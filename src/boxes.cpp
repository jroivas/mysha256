#include "boxes.hh"

uint32_t sha::Box::Ch(uint32_t e, uint32_t f, uint32_t g)
{
    return (e & f) ^ (~e & g);
}

uint32_t sha::Box::Ma(uint32_t a, uint32_t b, uint32_t c)
{
    return (a & b) ^ (a & c) ^ (b & c);
}

static uint32_t ror(uint32_t x, uint32_t bits) {
    return (x >> bits) | (x << (32 - bits));
}

uint32_t sha::Box::S0(uint32_t x)
{
    return ror(x, 2) ^ ror(x, 13) ^ ror(x, 22);
}

uint32_t sha::Box::S1(uint32_t x)
{
    return ror(x, 6) ^ ror(x, 11) ^ ror(x, 25);
}
