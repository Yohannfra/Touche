/*
** Assouline Yohann, 2020
** WSSF
** File description:
** constants
*/

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <Arduino.h>
#include <stdint.h>

extern const byte BUTTON_PIN;
extern const byte LED_PIN;
extern const uint8_t MAC_ADDR[];
extern const uint8_t SERVER_MAC_ADDR[];

extern const unsigned short FENCING_BLINKING_TIME;

typedef enum {
    ERROR,
    TOUCH
} payload_types_e;

#endif // CONSTANTS_HPP
