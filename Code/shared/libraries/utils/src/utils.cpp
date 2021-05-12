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

#include "utils.hpp"

#include "ArduinoLog.h"

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
    Log.notice(name, buff);
}

void utils::print_packet(packet_t packet)
{
    static int index = 0;

    Log.notice("===================================");
    Log.notice("Packet: %d", index);

    Log.notice("As decimal: %d", static_cast<int>(packet));
    utils::print_bin("As binary: ", packet);

    touche_role_e player_role = static_cast<touche_role_e>(GET_ROLE(packet));
    payload_type_e payload = static_cast<payload_type_e>(GET_PAYLOAD(packet));

    Log.notice("Role: %s", (player_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2"));
    utils::print_bin("Payload: ", payload);
    Log.notice("===================================");

    index += 1;
}
