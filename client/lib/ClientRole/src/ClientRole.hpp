#ifndef CLIENT_ROLE_HPP
#define CLIENT_ROLE_HPP

#include "protocol.h"

#include <stdint.h>

void printArduinoUniqueID();

wsff_role_e getBoardRole();

#ifdef WRITE_ROLE_TO_EEPROM
    void writeRoleToEEPROM(wsff_role_e role);
#endif

#endif // CLIENT_ROLE_HPP
