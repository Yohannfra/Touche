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

#include "WeaponButton.hpp"

#include "DebugLog.h"
#include "touche.h"

WeaponButton::WeaponButton(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

bool WeaponButton::isPressed() const
{
    bool state = !digitalRead(_pin);

    if (state) {
        unsigned long t1 = millis();

        while (!digitalRead(_pin) == state) {
            if (millis() - t1 > FENCING_MINIMUM_TIME_VALID_HIT) {
                // DEBUG_LOG_LN("EPEE BTN PRESSED");
                return true;
            }
        }
    }
    return false;
}
