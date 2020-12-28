/**
 * @file Led.hpp
 * @brief led class header
 * @author Assouline Yohann
 * @date 2020-12-24
 */

#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class Led
{
    private:
        /**
         * @brief state of the led
         */
        bool _state;

        /**
         * @brief led's pin
         */
        uint8_t _pin;

    public:
        /**
         * @brief default constructor
         */
        Led(uint8_t pin);

        /**
         * @brief get led state
         *
         * @return true if led is on else false
         */
        bool getState() const;

        /**
         * @brief turn led on
         */
        void turnOn();

        /**
         * @brief turn led off
         */
        void turnOff();

        /**
         * @brief blink led
         *
         * @param delay_ms the blinking delay
         */
        void blink(int delay_ms);
};

#endif /* LED_HPP */
