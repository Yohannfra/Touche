#ifndef RGBLED_HPP
#define RGBLED_HPP

#include <Arduino.h>

// A few colors definitions to use for the led
#define RGB_LED_COLOR_RED 0b100
#define RGB_LED_COLOR_GREEN 0b010
#define RGB_LED_COLOR_BLUE 0b001
#define RGB_LED_COLOR_MAGENTA 0b101
#define RGB_LED_COLOR_YELLOW 0b110

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
