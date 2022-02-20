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

#ifndef PLAYERCONFIG_HPP
#define PLAYERCONFIG_HPP

#include "../../../include/config.h"
#include "protocol.h"
#include "touche.h"

class PlayerConfig {
  public:
    PlayerConfig(touche_role_e role, weapon_mode_e weapon);

    void setWeapon(weapon_mode_e weapon);
    weapon_mode_e getWeapon() const;

    touche_role_e getRole() const;

    void setPisteMode(bool mode);
    bool getPisteMode() const;

  private:
    weapon_mode_e _weapon;
    touche_role_e _role;
    bool _pisteMode;
};

#endif /* PLAYERCONFIG_HPP */
