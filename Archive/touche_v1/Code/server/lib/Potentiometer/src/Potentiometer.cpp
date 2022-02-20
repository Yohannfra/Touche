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

#include "Potentiometer.hpp"

#include "ArduinoLog.h"

Potentiometer::Potentiometer(byte pin)
{
    _pin = pin;
}

int Potentiometer::getMappedValue()
{
    int val = analogRead(_pin);

    int max = 730;  // with a 5k pot

    return map(val, 0, max, 0, 255 /* after 200 it sounds bad (with a 5k pot */);
}

int Potentiometer::getRawValue()
{
    return analogRead(_pin);
}
