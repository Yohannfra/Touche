#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>

class Buzzer
{
private:
    byte pin;
public:
    Buzzer(byte pin);
    void play();
    void stop();
};

#endif /* BUZZER_HPP */