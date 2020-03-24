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

extern const uint8_t MAC_ADDR[];
extern const uint8_t SERVER_MAC_ADDR[];

extern const unsigned short FENCING_BLINKING_TIME;

typedef enum {
    ERROR,
    TOUCH
} payload_types_e;

typedef struct message_s {
    uint8_t id_sender[];
    payload_types_e payload;
}   message_t;

#endif // CONSTANTS_HPP
