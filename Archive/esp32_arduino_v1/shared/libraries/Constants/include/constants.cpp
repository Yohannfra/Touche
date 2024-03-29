#include "constants.hpp"

/*
* Those are the mac address of the boards i use to dev the project.
* To find the address of your boards use ../tools/get_esp32_mac_address/
* Then replace those addresses with yours.
* Be careful to keep in mind which will be the server and which the clients.
*
* You need to change both list in this file and respect the formatting
*/

const String MAC_ADDR_LIST_STR[][3] {
    {
        "24:62:AB:B0:73:50", // Server
        "A4:CF:12:6C:9C:54", // Client
        "3C:71:BF:FD:85:20"  // Client
    },
};

const uint8_t MAC_ADDR_LIST[][3][6] {
    {
        {0xA4, 0xCF, 0x12, 0x6C, 0x9C, 0x54}, // Client
        {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50}, // Server
        {0x3C, 0x71, 0xBF, 0xFD, 0x85, 0x20}  // Client
    },
};
