#include "EpeeButton.hpp"

EpeeButton::EpeeButton(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

bool EpeeButton::isPressed() const
{
    return digitalRead(_pin);
}