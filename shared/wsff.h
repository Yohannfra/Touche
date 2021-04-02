#ifndef WSFF_H
#define WSFF_H

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
#define FENCING_BLINKING_TIME (2000UL) // 2 secs

/**
 * @brief How long between two hits for it to be a double hit (ms)
 */
#define FENCING_LAPS_DOUBLE_TOUCH (50) // 50 ms

/**
 * @brief Minimum time a hit must last to be valid (ms)
 */
#define FENCING_MINIMUM_TIME_VALID_HIT (2) // 2 ms


/**
 * @brief The weapon mode to use, can be changed on runtime.
 * Mode is change by the push button on the server
 */
typedef enum {
    EPEE,
    FOIL,
    // SABRE // maybe one day
} weapon_mode_e;

// default weapon is epee because it's the best weapon :) but you can easily change that value
static const weapon_mode_e DEFAULT_WEAPON_MODE = EPEE;

#endif // WSFF_H