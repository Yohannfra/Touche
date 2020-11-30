#include <Arduino.h>
#include <ArduinoUniqueID.h>

#include "board_id.h"

#define TOTAL_BOARDS 3

static const uint8_t BOARDS_IDS[3][9] = {
    {0x55, 0x39, 0x36, 0x35, 0x30, 0x39, 0x10, 0x05, 0x19}, // 1
    {0x59, 0x38, 0x38, 0x31, 0x34, 0x39, 0x02, 0x09, 0x1A}, // 2
    {0x55, 0x39, 0x36, 0x35, 0x30, 0x39, 0x0D, 0x29, 0x19}
};

void printArduinoUniqueID()
{
    for(size_t i = 0; i < UniqueIDsize; i++) {
        Serial.print(UniqueID[i], HEX);
        Serial.print(" ");
    }
    Serial.println("");
}

int8_t getBoardId()
{
    int8_t ID[9] = {0};

    for (int i = 0; i < UniqueIDsize; i++) {
        ID[i] = UniqueID[i];
    }

    for (int i = 0; i < TOTAL_BOARDS; i++) {
        if (memcmp(ID, BOARDS_IDS[i], sizeof(ID)) == 0) {
            return i+1;
        }
    }
    return -1;
}
