#include "PlayerConfig.hpp"
#include <EEPROM.h>
#include "DebugLog.h"

// Addresses in EEPROM
#define ROLE_ADDR_IN_EEPROM 0x00
#define WEAPON_ADDR_IN_EEPROM 0x01

#if (PLAYER_ROLE != PLAYER_1 && PLAYER_ROLE != PLAYER_2)
    #error "PLAYER_ROLE must be PLAYER_1 or PLAYER_2"
#endif

#if (DEFAULT_WEAPON_MODE != EPEE && DEFAULT_WEAPON_MODE != FOIL)
    #if (DEFAULT_WEAPON_MODE === "SABRE")
        #error "Sabre weapon not implemente yet"
    #endif

    #error "DEFAULT_WEAPON_MODE must be EPEE or FOIL"
#endif

PlayerConfig::PlayerConfig(wsff_role_e role, weapon_mode_e weapon)
{
    wsff_role_e role_in_mem = static_cast<wsff_role_e>(EEPROM.read(ROLE_ADDR_IN_EEPROM));
    weapon_mode_e weapon_in_mem = static_cast<weapon_mode_e>(EEPROM.read(WEAPON_ADDR_IN_EEPROM));

    if ((role_in_mem != PLAYER_1 && role_in_mem != PLAYER_2) || FORCE_WRITE_PLAYER_ROLE) { // to avoid overwriting
        DEBUG_LOG_VAL("Overwriting player role from : ", role_in_mem == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
        DEBUG_LOG_VAL("To : ", role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
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

wsff_role_e PlayerConfig::getRole() const
{
    return _role;
}