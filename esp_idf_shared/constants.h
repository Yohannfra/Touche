#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <stdint.h>

#include "FencingConstants.h"

#define SERIAL_ID 1

#define SERVER_MAC_ADDR_INDEX 0
#define CLIENT_1_MAC_ADDR_INDEX 1
#define CLIENT_2_MAC_ADDR_INDEX 2

#define PLAYER_1 0
#define PLAYER_2 1

extern const char MAC_ADDR_LIST_STR[][3][20];
extern const uint8_t MAC_ADDR_LIST[][3][6];

/*
To access a specific board:

    Server:
        MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX]
    Board 1:
        MAC_ADDR_LIST[SERIAL_ID][CLIENT_1_MAC_ADDR_INDEX]
    Board 2:
        MAC_ADDR_LIST[SERIAL_ID][CLIENT_2_MAC_ADDR_INDEX]
*/

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
