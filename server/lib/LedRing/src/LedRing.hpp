#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../../include/server_config.h"
#include "../../ActionManager/src/ActionManager.hpp"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

#define RED_RGB (color_t){0xFF, 0, 0}
#define GREEN_RGB (color_t){0, 0xFF, 0}
#define ORANGE_RGB (color_t){0xFF, 0xA5, 0}

#define NEOPIXEL_RING_SIZE 12

#define NB_NEOPIXEL NEOPIXEL_RING_SIZE * NB_NEOPIXEL_RING


/**
 * @brief class to abstract neopixel ring usage
 *
 */
class LedRing
{
    private:
        /**
         * @brief Pin attached to neopixel's data pin
         *
         */
        byte pin;

        /**
         * @brief Adafruit_NeoPixel class instance
         *
         */
        Adafruit_NeoPixel strip;

    public:
        /**
         * @brief Construct a new Led Ring object
         *
         * @param pin Pin attached to neopixel's data pin
         */
        LedRing(byte pin);

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
        void set_color(color_t color, uint8_t index = 0);

        /**
         * @brief Set one color for half of the pixels and one for the other half
         *
         * @param color_1 color for first half
         * @param color_2 color for second half
         */
        void set_half_colors(color_t color_1, color_t color_2);

        /**
         * @brief blink all pixels
         *
         * @param color color to blink
         * @param time_ms blinking delay
         * @param nb_blinks number of blink to do
         * @param index index of the first neopixel
         */
        void blink(color_t color, int time_ms, size_t nb_blinks = 3, uint8_t index = 0);

        /**
         * @brief Do a nice circular annimation
         *
         * @param color color of the annimation
         */
        void do_circle_annimation(color_t color);


        void show_hits(hit_type_e hit_type);
};

#endif /* LEDRING_HPP */
