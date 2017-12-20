#include "boxes.hh"

uint32_t sha::Box::Ch(uint32_t e, uint32_t f, uint32_t g)
{
    return (e & f) ^ (~e & g);
}
