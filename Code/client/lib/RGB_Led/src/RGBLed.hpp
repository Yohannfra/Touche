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

#ifndef RGBLED_HPP
#define RGBLED_HPP

#include "touche.h"

#include <Arduino.h>

/**
 * @brief A class to abstract the use of a RGB led
 */
class RGBLed {
  public:
    // A few colors definitions to use for the led
    typedef enum {
        RED = 0b100,
        GREEN = 0b010,
        BLUE = 0b001,
        MAGENTA = 0b101,
        AQUA = 0b011,
        YELLOW = 0b110,
        NONE = 0b000,
    } color_e;

    /**
     * @brief A quick function to switch from weapon to color
     *
     * @param weapon weapon weapon
     * @return RGBLed::color_e color corresponding to the weapon
     */
    static inline RGBLed::color_e WEAPON_MODE_TO_COLOR(weapon_mode_e weapon)
    {
        return weapon == EPEE ? RGBLed::RED : weapon == FOIL ? RGBLed::BLUE : RGBLed::GREEN;
    }

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
    void setColor(RGBLed::color_e color);

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
    void blink(RGBLed::color_e color, int delayMs, int nbBlinks = 3);

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
