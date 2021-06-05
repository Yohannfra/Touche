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

#include "Weapon.hpp"

#include "ArduinoLog.h"
#include "touche.h"

Weapon::Weapon(uint8_t pinButton, VirtualGround &virtualGround) : _virtualGround(virtualGround), _pin(pinButton)
{
    pinMode(_pin, INPUT);
}

bool Weapon::buttonPressed()
{
    return digitalRead(_pin);
}

Weapon::hit_status_e Weapon::isHitting(weapon_mode_e weapon, bool checkVirtualGround)
{
    switch (weapon) {
        case EPEE:
            if (buttonPressed()) {
                unsigned long t1 = millis();

                while (buttonPressed()) {
                    if (millis() - t1 > FENCING_MINIMUM_TIME_VALID_HIT) {
                        // Log.trace("Epee button pressed");
                        if (checkVirtualGround) {
                            return _virtualGround.trigger_ground() ? INVALID : VALID;
                        } else {
                            return VALID;
                        }
                    }
                }
            }
            break;

        case FOIL:
            if (buttonPressed()) {
                unsigned long t1 = millis();

                while (buttonPressed()) {
                    if (millis() - t1 > FENCING_MINIMUM_TIME_VALID_HIT) {
                        // Log.trace("Foil button pressed");
                        if (checkVirtualGround) {
                            return _virtualGround.trigger_ground() ? VALID : INVALID;
                        } else {
                            return VALID;
                        }
                    }
                }
            }
            break;
            // add SABRE case here
    }
    return NONE;
}
