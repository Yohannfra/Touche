#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef uint8_t device_id_t;

typedef uint8_t packet_t;

/*
    A packet is 16 bits

    00000000 00000000

    The firsts byte is the id: IDIDIDID 00000000.
    The id is in the range [0:255]

    The second byte is the payload. here is the code used:
        8 bits -> 76543210
            7 :
            6 :
            5 : Calibration failed
            4 : Going to sleep (when client is unused for more than X minutes)
            3 : Calibration is done
            2 : Calibration started
            1 : HIT : When a player hit
            0 : GND : When a player gnd is touched
*/

#define ACK_BIT_MASK                      (0b00000001)
#define HIT_BIT_MASK                      (0b00000010)
#define GND_BIT_MASK                      (0b00000100)
#define CALIBRATION_STARTING_BIT_MASK     (0b00001000)
#define CALIBRATION_END_BIT_MASK          (0b00010000)
#define CLIENT_GOING_TO_SLEEP_BIT_MASK    (0b00100000)
#define CALIBRATION_FAILED_BIT_MASK       (0b01000000)

#define GET_ID(n) (n >> 3)

#define TO_ID(n) (n << 3)

#define IS_HIT(n) (n & HIT_BIT_MASK)
#define IS_GND(n) (n & GND_BIT_MASK)
#define IS_ACK(n) (n & ACK_BIT_MASK)

#endif // PROTOCOL_H