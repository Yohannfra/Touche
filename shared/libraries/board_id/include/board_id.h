#ifndef BOARD_ID_H
#define BOARD_ID_H

#include <stdint.h>

void printArduinoUniqueID();

int8_t getBoardId();


#ifdef WRITE_ID_TO_EEPROM
    void writeIdToEEPROM(uint8_t id);
#endif

#endif // BOARD_ID_H
