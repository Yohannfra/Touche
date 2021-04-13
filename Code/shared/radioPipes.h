#ifndef RADIOPIPES_H
#define RADIOPIPES_H

#include <stdint.h>

/*
    Modify this file to change the pipe and addresses used by the NRF24l01 modules.
 */

// Pipe used in nrf24l01 config
#define NRF24_WSFF_PIPE (0xE8E8F0F0E1LL)

static const uint64_t PIPES_ADDRESSES[2] = {
    0xB3B4B5B601LL, // Pipe player 1
    0xB3B4B5B602LL // Pipe player 2
};

#endif // RADIOPIPES_H
