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

#include "PlayerConfig.hpp"

#include "ArduinoLog.h"

#include <EEPROM.h>

// Addresses in EEPROM
#define ROLE_ADDR_IN_EEPROM 0x00
#define WEAPON_ADDR_IN_EEPROM 0x01

#if (PLAYER_ROLE != PLAYER_1 && PLAYER_ROLE != PLAYER_2)
    #error "PLAYER_ROLE must be PLAYER_1 or PLAYER_2"
#endif

#if (DEFAULT_WEAPON_MODE != EPEE && DEFAULT_WEAPON_MODE != FOIL)
    #if (DEFAULT_WEAPON_MODE == "SABRE")
        #error "Sabre weapon not implemente yet"
    #endif

    #error "DEFAULT_WEAPON_MODE must be EPEE or FOIL"
#endif

PlayerConfig::PlayerConfig(touche_role_e role, weapon_mode_e weapon)
{
    touche_role_e role_in_mem = static_cast<touche_role_e>(EEPROM.read(ROLE_ADDR_IN_EEPROM));
    weapon_mode_e weapon_in_mem = static_cast<weapon_mode_e>(EEPROM.read(WEAPON_ADDR_IN_EEPROM));

    if ((role_in_mem != PLAYER_1 && role_in_mem != PLAYER_2) || FORCE_WRITE_PLAYER_ROLE) {  // to avoid overwriting
        Log.notice("Overwriting player role from : %s to %s", role_in_mem == PLAYER_1 ? "PLAYER_1" : "PLAYER_2",
            role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
        EEPROM.update(ROLE_ADDR_IN_EEPROM, static_cast<uint8_t>(role));
        _role = role;
    } else {
        _role = role_in_mem;
    }

    if (weapon_in_mem != weapon) {  // to avoid unnecessary call to EEPROM.update
        this->setWeapon(weapon);
    } else {
        _weapon = weapon_in_mem;
    }
}

void PlayerConfig::setWeapon(weapon_mode_e weapon)
{
    _weapon = weapon;
    EEPROM.update(WEAPON_ADDR_IN_EEPROM, static_cast<uint8_t>(_weapon));
}

weapon_mode_e PlayerConfig::getWeapon() const
{
    return _weapon;
}

touche_role_e PlayerConfig::getRole() const
{
    return _role;
}
