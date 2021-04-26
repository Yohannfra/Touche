/*
WSFF Project
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

#include "utils.hpp"

#include "DebugLog.h"

#include <Arduino.h>

void utils::print_bin(const char *name, uint8_t n)
{
    char buff[9] = "00000000";

    for (int i = 0; i < 8; i++) {
        if (n & 1) {
            buff[7 - i] = '1';
        }
        n >>= 1;
    }
    DEBUG_LOG_VAL(name, buff);
}

void utils::print_packet(packet_t packet)
{
    static int index = 0;

    DEBUG_LOG_LN("===================================");
    DEBUG_LOG_VAL("Packet: ", index);

    DEBUG_LOG_VAL("As decimal: ", packet);
    utils::print_bin("As binary: ", packet);

    wsff_role_e player_role = static_cast<wsff_role_e>(GET_ROLE(packet));
    payload_type_e payload = static_cast<payload_type_e>(GET_PAYLOAD(packet));

    DEBUG_LOG_VAL("Role: ", (player_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2"));
    utils::print_bin("Payload: ", payload);
    DEBUG_LOG_LN("===================================");

    index += 1;
}