#include <Arduino.h>
#include "utils.hpp"
#include "board_id.h"

#ifdef DEBUG
void utils::print_bin(const char *name, uint8_t n)
{
    char buff[9] = "00000000";

    for (int i = 0; i < 8; i++) {
        if (n & 1) {
            buff[7 - i] = '1';
        }
        n >>= 1;
    }
    Serial.print(name);
    Serial.print(" : ");
    Serial.println(buff);
}

void utils::print_board_infos()
{
    Serial.println("=========== Board infos ===========");
    Serial.print("Arduino ID: ");
    printArduinoUniqueID();
    Serial.print("WSFF ID: ");
    Serial.println(getBoardId());
    Serial.println("===========     End     ===========");
}

#endif