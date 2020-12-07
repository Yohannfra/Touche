#include "Led.hpp"

/*
    The led pin is 5 (PD5)
    Using this method to make it faster
*/

#define LED_PIN (1 << 5)

Led::Led()
{
    _state = false;
    DDRD |= LED_PIN; // set led pin as output
}

bool Led::getState() const
{
    return _state;
}

void Led::turnOn()
{
    PORTD |= (LED_PIN);
    _state = true;
}

void Led::turnOff()
{
    PORTD &= ~(LED_PIN);
    _state = false;
}

void Led::blink(int delay_ms)
{
    this->turnOn();
    delay(delay_ms);
    this->turnOff();
}