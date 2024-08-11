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

/**
 * @brief Arduino pin used for the buzzer
 */
#define BUZZER_PIN 10

/**
 * @brief Arduino pin used for the potentiometer
 */
#define POTENTIOMETER_PIN A3

/**
 * @brief Arduino pin used for the piste mode button
 */

#define PIN_BUTTON_SWITCH_PLAYERS 4

#define PIN_BUTTON_PISTE_MODE 5

#define PIN_BUTTON_CHANGE_WEAPON 6

/**
 * @brief Arduino pin used for the neopixel ring
 */
#define LED_RING_PIN 3

/**
 * @brief Arduino pin for chip enable pin of NRF24L01
 */
#define NRF24L01_CE_PIN 7

/**
 * @brief Arduino pin for chip select pin of NRF24L01
 */
#define NRF24L01_CS_PIN 8

#endif /* CONFIG_H */
