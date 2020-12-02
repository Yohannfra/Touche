#ifndef EPEEBUTTON_HPP
#define EPEEBUTTON_HPP

#include <Arduino.h>

class EpeeButton
{
    private:
        uint8_t _pin;
    public:
        EpeeButton(uint8_t pin);
        bool isPressed() const;
};

#endif /* EPEEBUTTON_HPP */