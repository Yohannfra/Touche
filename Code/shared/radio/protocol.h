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

#include "../touche.h"

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    SERVER = 2,
} touche_role_e;

typedef uint8_t packet_t;

typedef enum {
    // hit
    HIT = 1,
    ERROR,
} payload_type_e;

static inline payload_type_e GET_PAYLOAD(packet_t p)
{
    return (payload_type_e)(p & 0b00111111);
}

static inline touche_role_e GET_ROLE(packet_t p)
{
    return (touche_role_e)(p >> 6);
}

static inline packet_t CREATE_PACKET(touche_role_e role, payload_type_e payload)
{
    return (packet_t)(payload | (role << 6));
}

#endif /* PROTOCOL_H */
