#pragma once

#include "message.hh"

namespace sha {

class Hash
{
public:
    Hash();
    void round(const sha::Message::Schedule &);
    const uint32_t *get() const;

private:
    uint32_t hash[8];
};

}
