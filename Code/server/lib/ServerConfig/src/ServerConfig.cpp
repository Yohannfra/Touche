#include "ServerConfig.hpp"
#include <EEPROM.h>

// Addresses in EEPROM

#define WEAPON_ADDR_IN_EEPROM 0x00

#if (DEFAULT_WEAPON_MODE != EPEE && DEFAULT_WEAPON_MODE != FOIL)
    #if (DEFAULT_WEAPON_MODE === "SABRE")
        #error "Sabre weapon not implemente yet"
    #endif

    #error "DEFAULT_WEAPON_MODE must be EPEE or FOIL"
#endif

ServerConfig::ServerConfig(weapon_mode_e weapon)
{
    weapon_mode_e weapon_in_mem = static_cast<weapon_mode_e>(EEPROM.read(WEAPON_ADDR_IN_EEPROM));

    if (weapon_in_mem != weapon) {  // to avoid unnecessary call to EEPROM.update
        this->setWeapon(weapon);
    } else {
        _weapon = weapon_in_mem;
    }
}

void ServerConfig::setWeapon(weapon_mode_e weapon)
{
    _weapon = weapon;
    EEPROM.update(WEAPON_ADDR_IN_EEPROM, static_cast<uint8_t>(_weapon));
}

weapon_mode_e ServerConfig::getWeapon() const
{
    return _weapon;
}