#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class Led
{
    private:
        uint8_t _pin;
        bool _state;
    public:
        Led(uint8_t pin);
        bool getState() const;
        void turnOn();
        void turnOff();
        void blink(int delay_ms);
};

#endif /* LED_HPP */