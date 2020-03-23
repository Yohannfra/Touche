/*
** Assouline Yohann, 2020
** WSSF
** File description:
** constants
*/

#include "constants.hpp"

// PINS :
const byte BUTTON_PIN = 17;
const byte LED_PIN = 16;

// ESP32 MAC ADDRESS
const uint8_t MAC_ADDR[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

 // ESP32 SERVER MAC ADDRESS
const uint8_t SERVER_MAC_ADDR[] = {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50};

// How long the leds turn on when a player hit (ms)
const unsigned short FENCING_BLINKING_TIME = 1000;
