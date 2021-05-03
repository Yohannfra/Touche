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

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "VirtualGround.hpp"
#include "touche.h"

#include <Arduino.h>

/**
 * @brief A wrapper for a button
 */
class Weapon {
  public:
    typedef enum {
        VALID,
        INVALID,
        NONE,
    } hit_status_e;

    /**
    * @brief Construct a new Epee Button object
    *
    * @param pin button bin
    */
    Weapon(uint8_t pinButton, VirtualGround &virtualGround);

    /**
    * @brief get if button is pressed and is for more than 2 ms (see why in touche.h)
    *
    * @return boolean with the state of the button
    */
    hit_status_e isHitting(weapon_mode_e weapon, bool checkVirtualGround = true);

  private:
    /**
     * @brief virtualGroud instance
     */
    VirtualGround &_virtualGround;

    /**
    * @brief button's pin
    */
    uint8_t _pin;
};

#endif /* WEAPON_HPP */
