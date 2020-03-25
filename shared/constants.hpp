/*
** Assouline Yohann, 2020
** WSSF
** File description:
** constants
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <Arduino.h>
#include <stdint.h>

#define SERIAL_ID 1

#define SERVER_MAC_ADDR_INDEX 0
#define CLIENT_1_MAC_ADDR_INDEX 1
#define CLIENT_2_MAC_ADDR_INDEX 2

extern const uint8_t MAC_ADDR_LIST[][3][6];
extern const String MAC_ADDR_LIST_STR[][3];

/*
To access a specific board:

    Server:
        MAC_ADDR_LIST[SERIAL_ID][SERVER_MAC_ADDR_INDEX]
    Board 1:
        MAC_ADDR_LIST[SERIAL_ID][CLIENT_1_MAC_ADDR_INDEX]
    Board 2:
        MAC_ADDR_LIST[SERIAL_ID][CLIENT_2_MAC_ADDR_INDEX]
*/

/* extern const uint8_t MAC_ADDR[]; */
/* extern const uint8_t SERVER_MAC_ADDR[]; */

extern const unsigned short FENCING_BLINKING_TIME;

typedef enum {
    ERROR,
    HIT
} payload_types_e;

typedef struct message_s {
    unsigned short index_sender;
    payload_types_e payload;
}   message_t;

#endif // CONSTANTS_HPP
