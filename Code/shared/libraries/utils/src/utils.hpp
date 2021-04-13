#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdint.h>
#include "protocol.h"

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
}
#endif // UTILS_HPP
