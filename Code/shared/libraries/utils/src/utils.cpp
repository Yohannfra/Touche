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
    Log.notice("%s %s", name, buff);
}

void utils::print_packet(packet_t packet)
{
    static int index = 0;

    Log.trace("===================================");
    Log.notice("Packet: %d", index);

    Log.notice("As decimal: %d", static_cast<int>(packet));
    utils::print_bin("As binary: ", packet);

    touche_role_e player_role = static_cast<touche_role_e>(GET_ROLE(packet));
    payload_type_e payload = static_cast<payload_type_e>(GET_PAYLOAD(packet));

    Log.notice("Role: %s", (player_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2"));
    utils::print_bin("Payload: ", payload);
    Log.trace("===================================");

    index += 1;
}

void utils::print_ack_payload(ack_payload_t payload)
{
    Log.notice("Ack payload :");

    if (payload == ACK_ERROR) {
        Log.warning("ack is ACK_ERROR");
        return;
    }

    utils::print_bin("As binary: ", payload);
    Log.notice("Piste enabled : %s", (payload & ACK_PISTE_MODE) ? "True" : "False");
    Log.notice("Weapon : %s", payload & ACK_EPEE ? "EPEE" : payload & ACK_FOIL ? "FOIL" : "SABRE");
}
