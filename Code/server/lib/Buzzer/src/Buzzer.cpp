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

#include "Buzzer.hpp"

Buzzer::Buzzer(byte pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void Buzzer::play(uint8_t volume)
{
    analogWrite(_pin, volume);
}

void Buzzer::stop()
{
    analogWrite(_pin, 0);
}
