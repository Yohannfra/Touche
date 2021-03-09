#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define RED_RGB 0xFF, 0, 0
#define GREEN_RGB 0, 0xFF, 0
#define ORANGE_RGB 0xFF, 0xA5, 0

static const uint8_t COLOR_CODE[2][3] = {{RED_RGB}, {GREEN_RGB}};

#define NB_NEOPIXEL 12

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
         * @param r red
         * @param g green
         * @param b blue
         */
        void set_color(byte r, byte g, byte b);

        /**
         * @brief Set one color for half of the pixels and one for the other half
         *
         * @param r red for color 1
         * @param g green for color 1
         * @param b blue for color 1
         * @param r2 red for color 2
         * @param g2 green for color 2
         * @param b2 blue for color 2
         */
        void set_half_colors(byte r, byte g, byte b,
                        byte r2, byte g2, byte b2);
        /**
         * @brief blink all pixels
         *
         * @param r red
         * @param g green
         * @param b blue
         * @param time_ms blinking delay
         * @param nb_blinks number of blink to do
         */
        void blink(byte r, byte g, byte b, int time_ms, size_t nb_blinks = 3);

        /**
         * @brief blink all pixels
         *
         * @param rgb red/green/blue
         * @param time_ms blinking delay
         * @param nb_blinks number of blink to do
         */
        void blink(const uint8_t rgb[3], int time_ms, size_t nb_blinks = 3);

        /**
         * @brief Do a nice circular annimation
         *
         * @param r red
         * @param g green
         * @param b blue
         */
        void do_circle_annimation(byte r, byte g, byte b);
};

#endif /* LEDRING_HPP */