#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef uint8_t device_id_t;

typedef uint8_t packet_t;

/*
    A packet is 8 bits

    00000000

    The 5 firsts bits are the id: IDIDI---

    The 3 lasts bits are the action: -----GHA
        G -> GND : When a player gnd is touched
        H -> HIT : When a player hit
        A -> ACK : UNUSED FOR NOW
*/

#define PLAYER_1 0
#define PLAYER_2 1

#define ACK 0b00000001
#define HIT 0b00000010
#define GND 0b00000100

#define GET_ID(n) (n >> 3)

#define TO_ID(n) (n << 3)

#define IS_HIT(n) (n & HIT)
#define IS_GND(n) (n & GND)
#define IS_ACK(n) (n & ACK)

#endif // PROTOCOL_H