#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>

#include "FencingConstants.h"

#define PLAYER_1 0
#define PLAYER_2 1

typedef enum {
    NONE,
    ERROR,
    HIT,
    GROUND
} payload_types_e;

#define UNITIALIZED_MAC_ADDR (uint8_t[6]){0, 0, 0, 0, 0, 0}

#define CMP_MAC_ADDR(src, dest) memcmp(src, dest, sizeof(uint8_t) * 6)

typedef struct message_s {
    uint8_t sender_mac_addr[6];
    int capsensValue;
    payload_types_e payload;
}   message_t;

#endif // CONSTANTS_HPP
