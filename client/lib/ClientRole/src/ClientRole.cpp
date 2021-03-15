#include <Arduino.h>
#include "ClientRole.hpp"
#include <EEPROM.h>

#define ROLE_ADDR_IN_EEPROM 0x00

#ifdef WRITE_ROLE_TO_EEPROM

void writeRoleToEEPROM(wsff_role_e role)
{
    EEPROM.update(ROLE_ADDR_IN_EEPROM, role);
}
#endif

wsff_role_e getBoardRole()
{
    return (wsff_role_e)EEPROM.read(ROLE_ADDR_IN_EEPROM);
}
