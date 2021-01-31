#include <Arduino.h>
#include "board_id.h"
#include <EEPROM.h>

#define ID_ADDR_IN_EEPROM 0x00

static const uint8_t USED_BOARDS_IDS[] = {
    1,
    2
};

#ifdef WRITE_ID_TO_EEPROM
    void writeIdToEEPROM(uint8_t id)
    {
        EEPROM.update(ID_ADDR_IN_EEPROM, id);
    }
#endif

void printArduinoUniqueID()
{
    Serial.println(getBoardId());
}

int8_t getBoardId()
{
    return EEPROM.read(ID_ADDR_IN_EEPROM);
}
