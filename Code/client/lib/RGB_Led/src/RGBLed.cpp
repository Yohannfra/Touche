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

#include "RGBLed.hpp"

RGBLed::RGBLed(uint8_t pinR, uint8_t pinG, uint8_t pinB) : _pinR(pinR), _pinG(pinG), _pinB(pinB)
{
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void RGBLed::setColor(RGBLed::color_e color)
{
    digitalWrite(_pinR, bitRead(color, 2));
    digitalWrite(_pinG, bitRead(color, 1));
    digitalWrite(_pinB, bitRead(color, 0));
}

void RGBLed::turnOff()
{
    this->setColor(NONE);
}

void RGBLed::blink(RGBLed::color_e color, int delayMs, int nbBlinks)
{
    for (int i = 0; i < nbBlinks; i++) {
        this->setColor(color);
        delay(delayMs);
        this->turnOff();
        delay(delayMs);
    }
}
