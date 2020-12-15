#include "Buzzer.hpp"

Buzzer::Buzzer(byte pin)
{
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void Buzzer::play()
{
    digitalWrite(this->pin, HIGH);
}

void Buzzer::stop()
{
    digitalWrite(this->pin, LOW);
}