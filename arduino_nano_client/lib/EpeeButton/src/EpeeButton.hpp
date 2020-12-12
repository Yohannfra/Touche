#ifndef EPEEBUTTON_HPP
#define EPEEBUTTON_HPP

#include <Arduino.h>

class EpeeButton
{
    private:
    public:
        EpeeButton();
        bool isPressed() const;
};

#endif /* EPEEBUTTON_HPP */
