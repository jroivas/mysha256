#pragma once

#include <cstdint>

namespace sha {
namespace Box {

uint32_t Ch(uint32_t, uint32_t, uint32_t);
uint32_t Ma(uint32_t, uint32_t, uint32_t);

}
}
