/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** LedRing
*/

#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Adafruit_NeoPixel.h>

#define LED_COUNT (12)
#define LED_RING_TYPE (NEO_GRB + NEO_KHZ800)

class LedRing {
    public:
        LedRing(int pin);
        ~LedRing() = default;
        void setAllColors(char r, char g, char b);

    private:
        Adafruit_NeoPixel _strip;
};

#endif // LEDRING_HPP
