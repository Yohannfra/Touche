/*
Touché Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "touche.h"

#include <stdint.h>

typedef enum : uint8_t {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    SERVER = 2,
} touche_role_e;

/* --------------------- Packet -------------------------------- */

typedef uint8_t packet_t;

typedef enum : uint8_t {
    // hit
    HIT = 1,
    INVALID_HIT,

    // Calibration
    CALIBRATION_STARTING,
    CALIBRATION_END,
    CALIBRATION_FAILED,

    // changing weapon
    CHANGING_TO_EPEE,
    CHANGING_TO_FOIL,
    CHANGING_TO_SABRE,

    // piste mode
    ENABLE_PISTE_MODE,
    DISABLE_PISTE_MODE,
} payload_type_e;

static inline payload_type_e GET_PAYLOAD(packet_t p)
{
    return static_cast<payload_type_e>(p & 0b00111111);
}

static inline touche_role_e GET_ROLE(packet_t p)
{
    return static_cast<touche_role_e>(p >> 6);
}

static inline packet_t CREATE_PACKET(touche_role_e role, payload_type_e payload)
{
    return static_cast<packet_t>(payload | (role << 6));
}

/* ------------------------------------------------------------- */

/* --------------------- Ack payload --------------------------- */

/* Custom ack payload

Custom ack is 8 bits

76543210 :
7 : -
6 : -
5 : -
4 : -
3 : piste mode enabled / disabled
2 : EPEE
1 : SABRE
0 : FOIL
*/

typedef uint8_t ack_payload_t;

typedef enum : uint8_t {
    ACK_PISTE_MODE = (1 << 7),
    ACK_SABRE = (1 << 2),
    ACK_FOIL = (1 << 1),
    ACK_EPEE = (1 << 0),
} ack_payload_type_e;

static inline ack_payload_t CREATE_ACK_PAYLOAD(bool pisteEnabled, weapon_mode_e weapon)
{
    return static_cast<ack_payload_t>((pisteEnabled << 7) | (1 << weapon));
}

/* ------------------------------------------------------------- */

#endif  // PROTOCOL_H
