#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include "../../../include/config.h"
#include "protocol.h"
#include "wsff.h"

class ServerConfig {
    public:
        ServerConfig(weapon_mode_e weapon);

        void setWeapon(weapon_mode_e weapon);
        weapon_mode_e getWeapon() const;

    private:
        weapon_mode_e _weapon;
};

#endif /* SERVERCONFIG_HPP */
