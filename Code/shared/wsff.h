/*
WSFF Project
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

#ifndef WSFF_H
#define WSFF_H

#include <stdint.h>

// This file contains all important fencing constants that must be known across the project

/* See this document : https://static.fie.org/uploads/25/126156-book%20m%20ang.pdf

TLDR of importants part (for this project).

---

Page 82 part b:
'[...] If the interval of time
between two hits is less than 40 ms (1/25th of a second), the apparatus must register a
double hit (both signal lamps must light up simultaneously). When the interval is
greater than 50 ms (1/20 of a second) the apparatus must register only one hit (only
one signal lamp is lit). The tolerance allowed for timing the apparatus is that between
these two limits (1/25th and 1/20th of a second)'

-> So the time for a double hit must be somewhere beetween 0 and 50 ms,
I set the threshold to 50 ms because nrf24l01 messages can be quite slow sometimes.

---

Page 82 part c:
'[...] The apparatus must not register signals of less than 2 ms duration.'

-> So if a hit occure i must check it last more than 2 ms before sending a hit message

---

Page 84 part a number 3:
'The audible signal will consist of either one short ring or a continuous note lasting
1–2 seconds, simultaneous with the light signals. The sound will be the same for
both sides of the apparatus'

-> I choosed to make it last 2 seconds to make it easier to see

---
*/

/**
 * @brief How long the led and buzzer signal lasts (ms)
 */
#define FENCING_BLINKING_TIME (2000UL)  // 2 secs

/**
 * @brief How long between two hits for it to be a double hit (ms)
 */
#define FENCING_LAPS_DOUBLE_TOUCH (50)  // 50 ms

/**
 * @brief Minimum time a hit must last to be valid (ms)
 */
#define FENCING_MINIMUM_TIME_VALID_HIT (2)  // 2 ms

/**
 * @brief The weapon mode to use, can be changed on runtime.
 * Mode is change by the push button on the server
 */
typedef enum : uint8_t {
    EPEE = 0,
    FOIL = 1,
    // SABRE // maybe one day
} weapon_mode_e;

// default weapon is epee because it's the best weapon :) but you can easily change this value
#define DEFAULT_WEAPON_MODE EPEE

#endif  // WSFF_H
