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

#include "ArduinoLog.h"
#include "Buzzer.hpp"
#include "LedRing.hpp"

#include <Arduino.h>

extern LedRing led_ring;

void do_calib()
{
    static unsigned int index = 0;

    led_ring.do_circle_annimation(ORANGE_RGB, index % 24);
    index++;

    if (index > 24) {
        index = 0;
    }
}
