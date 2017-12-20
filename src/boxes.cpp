#include "boxes.hh"

uint32_t sha::Box::Ch(uint32_t e, uint32_t f, uint32_t g)
{
    return (e & f) ^ (~e & g);
}

uint32_t sha::Box::Ma(uint32_t a, uint32_t b, uint32_t c)
{
    return 0;
}
