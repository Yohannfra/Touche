#include "Led.hpp"

Led::Led(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    _state = false;
}

bool Led::getState() const
{
    return _state;
}

void Led::turnOn()
{
    digitalWrite(_pin, HIGH);
    _state = true;
}

void Led::turnOff()
{
    digitalWrite(_pin, LOW);
    _state = false;
}

void Led::blink(int delay_ms)
{
    this->turnOn();
    delay(delay_ms);
    this->turnOff();
}
