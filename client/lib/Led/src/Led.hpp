#ifndef LED_HPP
#define LED_HPP

#include <Arduino.h>

class Led
{
    private:
        bool _state;
    public:
        Led();
        bool getState() const;
        void turnOn();
        void turnOff();
        void blink(int delay_ms);
};

#endif /* LED_HPP */