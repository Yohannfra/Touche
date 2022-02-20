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

#ifndef UTILS_HPP
#define UTILS_HPP

#include "protocol.h"

#include <stdint.h>

namespace utils {

    /**
     * @brief print an uint8_t in binary
     *
     * @param name name of the number to print
     * @param n number to print
     */
    void print_bin(const char *name, uint8_t n);

    /**
     * @brief print a few infos about the arduino
     */
    void print_board_infos();

    /**
     * @brief print a packet_t
     *
     * @param packet the packet to print
     */
    void print_packet(packet_t packet);

    /**
     * @brief print a payload
     *
     * @param payload the payload to print
     */
    void print_ack_payload(ack_payload_t payload);
}  // namespace utils
#endif  // UTILS_HPP
