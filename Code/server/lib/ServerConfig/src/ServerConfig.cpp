/*
Touché Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ServerConfig.hpp"

#include <EEPROM.h>

// Addresses in EEPROM

#define WEAPON_ADDR_IN_EEPROM 0x00

#if (DEFAULT_WEAPON_MODE != EPEE && DEFAULT_WEAPON_MODE != FOIL)
    #if (DEFAULT_WEAPON_MODE == "SABRE")
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
