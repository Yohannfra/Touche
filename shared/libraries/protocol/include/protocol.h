#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

// Pipe used in nrf24l01 config
#define NRF24_WSFF_PIPE (0xE8E8F0F0E1LL)

/*
    A packet is 8 bits:
        8 bits -> 76543210
            7 : Player_1 or Player_2 (0 - 1)
            6 :
            5 : Calibration failed
            4 : Going to sleep (when client is unused for more than X minutes)
            3 : Calibration is done
            2 : Calibration started
            1 : HIT : When a player hit
            0 : GND : When a player gnd is touched
*/

typedef uint8_t packet_t;

// typedef uint8_t device_id_t;

#define GET_ROLE(n) (n >> 7)

typedef enum {
    GND                     = (uint8_t)(1 << 0),
    HIT                     = (uint8_t)(1 << 1),
    CALIBRATION_STARTING    = (uint8_t)(1 << 2),
    CALIBRATION_END         = (uint8_t)(1 << 3),
    CLIENT_GOING_TO_SLEEP   = (uint8_t)(1 << 4),
    CALIBRATION_FAILED      = (uint8_t)(1 << 5),
}   payload_type_e;

#define BIT_MASK_ID_PLAYER_1 0
#define BIT_MASK_ID_PLAYER_2 (uint8_t)(1 << 7)

typedef enum {
    PLAYER_1 = (uint8_t)0,
    PLAYER_2 = (uint8_t)1,
    SERVER = (uint8_t)2,
    UNKNOWN = (uint8_t)3,
} wsff_role_e;

#endif // PROTOCOL_H