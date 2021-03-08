#ifndef UTILS_HPP
#define UTILS_HPP

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
}
#endif // UTILS_HPP
