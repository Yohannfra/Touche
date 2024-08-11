/*
Touché Project
Copyright (C) 2024 Assouline Yohann

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

#ifndef CONFIG_H
#define CONFIG_H

// ------ Config ------------

// Change that to 1 if you want to change a board from PLAYER_1 to PLAYER_2
// but reflash with 0 after doing so to preserve EEPROM
#define FORCE_WRITE_PLAYER_ROLE 0

#ifndef PLAYER_ROLE
    #define PLAYER_ROLE PLAYER_1  // change value to PLAYER_1 or PLAYER_2
#endif

// ------ Pinout ------------

/**
 * @brief Arduino pin used for the led
 */
#define LED_PIN_RED 10
#define LED_PIN_GREEN 6
#define LED_PIN_BLUE 9

/**
 * @brief Arduino pin for the button of the weapon
 */
#define EPEE_BUTTON_PIN 3

/**
 * @brief Arduino pin for chip enable pin of NRF24L01
 */
#define NRF24L01_CE_PIN 7

/**
 * @brief Arduino pin for chip select pin of NRF24L01
 */
#define NRF24L01_CS_PIN 8

/**
 * @brief Arduino pin for capacitive sensor in
 */
#define VIRTUAL_PIN_IN 2

/**
 * @brief Arduino pin for capacitive sensor out
 */
#define VIRTUAL_PIN_OUT 4

#endif  // CONFIG_H
