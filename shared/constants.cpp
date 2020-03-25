/*
** Assouline Yohann, 2020
** WSSF
** File description:
** constants
*/

#include "constants.hpp"

const String MAC_ADDR_LIST_STR[][3] {
    {
        "24:62:AB:B0:73:50", // SERVER
        "A4:CF:12:6C:9C:54", // Client
        "3C:71:BF:FD:85:20"  // Client
    },
    // ...
};

const uint8_t MAC_ADDR_LIST[][3][6] {
    {
        {0xA4, 0xCF, 0x12, 0x6C, 0x9C, 0x54},
        {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50},
        {0x3C, 0x71, 0xBF, 0xFD, 0x85, 0x20}
    },
    // ...
};