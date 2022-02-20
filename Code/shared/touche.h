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

#ifndef TOUCHE_H
#define TOUCHE_H

#include <stdint.h>

/**
 * @brief How long the led and buzzer signal lasts (ms)
 */
#define FENCING_BLINKING_TIME (2000UL) // 2 secs

/**
 * @brief How long between two hits for it to be a double hit (ms)
 */
#define FENCING_LAPS_DOUBLE_HIT (300) // 300 ms

#endif // TOUCHE_H
