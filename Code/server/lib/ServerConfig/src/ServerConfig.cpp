/*
Touché Project
Copyright (C) 2024 Assouline Yohann

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

#include "ArduinoLog.h"

#include <EEPROM.h>

// Addresses in EEPROM

#define WEAPON_ADDR_IN_EEPROM 0x00

#if (DEFAULT_WEAPON_MODE != EPEE && DEFAULT_WEAPON_MODE != FOIL)
    #if (DEFAULT_WEAPON_MODE == "SABRE")
        #error "Sabre weapon not implemente yet"
    #endif

    #error "DEFAULT_WEAPON_MODE must be EPEE or FOIL"
#endif

ServerConfig::ServerConfig(weapon_mode_e defaultWeapon) : _pisteMode(false)
{
    weapon_mode_e weapon_in_mem = static_cast<weapon_mode_e>(EEPROM.read(WEAPON_ADDR_IN_EEPROM));

    switch (weapon_in_mem) {
        case EPEE:
            _weapon = EPEE;
            break;
        case FOIL:
            _weapon = FOIL;
            break;
        // case SABRE:
        //     _weapon = SABRE;
        //     break;
        default:
            this->setWeapon(defaultWeapon);
            break;
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

void ServerConfig::setPisteMode(bool mode)
{
    _pisteMode = mode;
    // pisteMode is not written to EEPROM
}

bool ServerConfig::getPisteMode() const
{
    return _pisteMode;
}