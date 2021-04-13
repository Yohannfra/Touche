#include "RGBLed.hpp"

RGBLed::RGBLed(uint8_t pinR, uint8_t pinG, uint8_t pinB) :
    _pinR(pinR), _pinG(pinG), _pinB(pinB)
{
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
}

void RGBLed::setColor(uint8_t color)
{
    digitalWrite(_pinR, bitRead(color, 2));
    digitalWrite(_pinG, bitRead(color, 1));
    digitalWrite(_pinB, bitRead(color, 0));
}

void RGBLed::turnOff()
{
    this->setColor(0);
}

void RGBLed::blink(uint8_t color, int delayMs, int nbBlinks)
{
    for (int i = 0; i < nbBlinks; i++) {
        this->setColor(color);
        delay(delayMs);
        this->turnOff();
        delay(delayMs);
    }
}
