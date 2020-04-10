/*
** EPITECH PROJECT, 2020
** DefaultName
** File description:
** led_ring
*/

#include "LedRing.hpp"

LedRing::LedRing(int pin) : _strip(LED_COUNT, pin, LED_RING_TYPE)
{
    _strip.begin();
    _strip.show();
}

void LedRing::setAllColors(char r, char g, char b)
{
    for (int i = 0; i < LED_COUNT; i++)
        _strip.setPixelColor(i, r, g, b);
}
