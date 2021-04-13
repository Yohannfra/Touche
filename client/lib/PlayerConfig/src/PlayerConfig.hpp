#ifndef PLAYERCONFIG_HPP
#define PLAYERCONFIG_HPP

#include "../../../include/config.h"
#include "protocol.h"
#include "wsff.h"

class PlayerConfig {
    public:
        PlayerConfig(wsff_role_e role, weapon_mode_e weapon);

        void setWeapon(weapon_mode_e weapon);
        weapon_mode_e getWeapon() const;

        wsff_role_e getRole() const;

    private:
        weapon_mode_e _weapon;
        wsff_role_e _role;
};

#endif /* PLAYERCONFIG_HPP */
