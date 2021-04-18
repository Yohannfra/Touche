#ifndef RADIOPIPES_H
#define RADIOPIPES_H

#include <stdint.h>

/*
    Modify this file to change the addresses used by the NRF24l01 modules.
 */

static const uint64_t PIPES_ADDRESSES[2] = {
    0xB3B4B5B601LL, // PLAYER 1
    0xB3B4B5B602LL  // PLAYER 2
};

#endif // RADIOPIPES_H
