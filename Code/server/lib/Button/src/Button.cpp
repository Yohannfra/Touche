#include "Button.hpp"

Button::Button(uint8_t pin) : _pin(pin)
{
    pinMode(_pin, INPUT_PULLUP);
}

bool Button::isPressed()
{
    return !digitalRead(_pin);
}