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

#ifndef LEDRING_HPP
#define LEDRING_HPP

#include "../../../include/config.h"
#include "../../ActionManager/src/ActionManager.hpp"

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

static constexpr color_t NONE_RGB = {0, 0, 0};
static constexpr color_t RED_RGB = {0xFF, 0, 0};
static constexpr color_t GREEN_RGB = {0, 0xFF, 0};
static constexpr color_t ORANGE_RGB = {0xFF, 0xA5, 0};

#define NEOPIXEL_RING_SIZE 12

/**
 * @brief class to abstract neopixel ring usage
 *
 */
class LedRing {
  public:
    /**
    * @brief Construct a new Led Ring object
    *
    * @param pin Pin attached to neopixel's data pin
    */
    explicit LedRing(byte pin);

    /**
    * @brief Initialize neopixel ring
    *
    */
    void init();

    /**
    * @brief Turn all leds off
    *
    */
    void turn_off();

    /**
    * @brief Set the color of all neopixels
    *
    * @param color the color as rgb
    * @param index index of the first neopixel
    */
    void set_color(color_t color, uint8_t start = 0, uint8_t end = NEOPIXEL_RING_SIZE);

    /**
    * @brief blink all pixels
    *
    * @param color color to blink
    * @param time_ms blinking delay
    * @param nb_blinks number of blink to do
    * @param index index of the first neopixel
    */
    void blink(color_t color, int time_ms, size_t nb_blinks = 3, uint8_t index = 0);

    void blinkBoth(color_t color, color_t color2, int time_ms, size_t nb_blinks = 3);

    /**
    * @brief Do a nice circular annimation
    *
    * @param color color of the annimation
    * @param step current step in the annimation
    */
    void do_circle_annimation(color_t color);

    void show_hits(uint16_t hits);

    void switchColors();

    color_t getPlayerColor(touche_role_e player);

  private:
    /**
    * @brief Adafruit_NeoPixel class instance
    *
    */
    Adafruit_NeoPixel strip;

    color_t _colorPlayer1;

    color_t _colorPlayer2;

    uint8_t _sides[2];
};

#endif /* LEDRING_HPP */
