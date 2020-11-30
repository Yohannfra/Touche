#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef uint8_t device_id_t;

typedef uint8_t packet_t;

#define PLAYER_1 0
#define PLAYER_2 1

#define ACK 0b00000001
#define HIT 0b00000010
#define GND 0b00000100

#define GET_ID(n) (n >> 3)

#define TO_ID(n) (n << 3)

// #define IS_ACTION_ACK(n) (n & ACK)

#endif // PROTOCOL_H
