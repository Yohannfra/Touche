#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef uint16_t packet_t;

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

typedef uint8_t device_id_t;

#define GET_ID(n) (n >> 8)

typedef enum {
    ACK                     = (uint8_t)(1 << 0),
    HIT                     = (uint8_t)(1 << 1),
    GND                     = (uint8_t)(1 << 2),
    CALIBRATION_STARTING    = (uint8_t)(1 << 3),
    CALIBRATION_END         = (uint8_t)(1 << 4),
    CLIENT_GOING_TO_SLEEP   = (uint8_t)(1 << 5),
    CALIBRATION_FAILED      = (uint8_t)(1 << 6),
}   payload_type_e;

#endif // PROTOCOL_H