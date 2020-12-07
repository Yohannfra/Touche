#include "EpeeButton.hpp"

/*
    The button pin is 3 (PD3)
    Using this method to make it faster
*/

#define BUTTON_PIN (1 << 3) // PD3

EpeeButton::EpeeButton()
{
    DDRD &= ~BUTTON_PIN; // set pin 3 as input
}

bool EpeeButton::isPressed() const
{
    return PIND & BUTTON_PIN; // read pin 3
}