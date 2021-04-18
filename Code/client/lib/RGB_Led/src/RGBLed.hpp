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

#ifndef RGBLED_HPP
#define RGBLED_HPP

#include <Arduino.h>

// A few colors definitions to use for the led
#define RGB_LED_COLOR_RED 0b100
#define RGB_LED_COLOR_GREEN 0b010
#define RGB_LED_COLOR_BLUE 0b001
#define RGB_LED_COLOR_MAGENTA 0b101
#define RGB_LED_COLOR_AQUA 0b011
#define RGB_LED_COLOR_YELLOW 0b110

// Listen to server color
#define COLOR_LISTEN_TO_SERVER_MODE RGB_LED_COLOR_AQUA

// weapons color
#define COLOR_EPEE_MODE RGB_LED_COLOR_MAGENTA
#define COLOR_FOIL_MODE RGB_LED_COLOR_BLUE
#define COLOR_SABRE_MODE RGB_LED_COLOR_YELLOW

// epee
#define COLOR_EPEE_HIT RGB_LED_COLOR_GREEN

// foil
#define COLOR_FOIL_VALID_HIT RGB_LED_COLOR_GREEN
#define COLOR_FOIL_INVALID_HIT RGB_LED_COLOR_RED

// sabre
#define COLOR_SABRE_HIT RGB_LED_COLOR_GREEN

// Usefull define to get color from weapon mode
#define WEAPON_MODE_TO_COLOR(mode) (mode == EPEE ? COLOR_EPEE_MODE : \
                                        mode == FOIL ? COLOR_FOIL_MODE : \
                                        COLOR_SABRE_MODE)

/**
 * @brief A class to abstract the use of a RGB led
 */
class RGBLed {
    public:
       /**
        * @brief Construct a new RGBLed object
        *
        * @param pinR arduino pin connected to the red
        * @param pinG arduino pin connected to the green
        * @param pinB arduino pin connected to the blue
        */
        RGBLed(uint8_t pinR, uint8_t pinG, uint8_t pinB);

        /**
         * @brief Set the color of the led
         *
         * @param color the color to set
         */
        void setColor(uint8_t color);

        /**
         * @brief Turn off the led
         */
        void turnOff();

        /**
         * @brief blink the led
         *
         * @param color the color to use
         * @param delayMs blinking delay
         * @param nbBlinks number of times to blink
         */
        void blink(uint8_t color, int delayMs, int nbBlinks = 3);

    private:
        /**
         * @brief arduino pin connected to the red
         */
        uint8_t _pinR;

        /**
         * @brief arduino pin connected to the green
         */
        uint8_t _pinG;

        /**
         * @brief arduino pin connected to the blue
         */
        uint8_t _pinB;
};

#endif  // RGBLED_HPP
