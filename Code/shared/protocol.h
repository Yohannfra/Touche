#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

typedef uint8_t packet_t;

typedef enum : uint8_t {
    // hit
    HIT                      = 1,

    // Calibration
    CALIBRATION_STARTING     = 2,
    CALIBRATION_END          = 3,
    CALIBRATION_FAILED       = 4,

    // changing weapon
    CHANGING_TO_EPEE         = 5,
    CHANGING_TO_FOIL         = 6,
    CHANGING_TO_SABRE        = 7,

    // piste mode
    ENABLE_PISTE_MODE        = 8,
    DISABLE_PISTE_MODE       = 9,
} payload_type_e;

#define GET_PAYLOAD(n) (n & 0b00111111)

#define GET_ROLE(n) (n >> 6)

#define CREATE_PACKET(role, payload) (payload | (role << 6))

#define GET_OTHER_WEAPON_MODE(current_mode) ((current_mode == EPEE) ? FOIL : EPEE)

typedef enum : uint8_t {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    SERVER = 2,
} wsff_role_e;

#endif // PROTOCOL_H
