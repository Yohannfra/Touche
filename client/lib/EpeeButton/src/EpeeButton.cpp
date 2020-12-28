/**
 * @file EpeeButton.cpp
 * @brief epee button class
 * @author Assouline Yohann
 * @date 2020-12-24
 */

#include "EpeeButton.hpp"

EpeeButton::EpeeButton(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

bool EpeeButton::isPressed() const
{
    return !digitalRead(_pin); // is inversed becaused of INPUT_PULLUP
}
