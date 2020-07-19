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

typedef struct message_s {
    unsigned short index_sender;
    int capsensValue;
    payload_types_e payload;
}   message_t;

#endif // CONSTANTS_HPP
