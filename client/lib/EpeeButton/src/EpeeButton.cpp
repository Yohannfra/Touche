#include "EpeeButton.hpp"

/*
    The button pin is 3 (PD3)
    Using this method to make it faster
*/

#define BUTTON_PIN (3)
#define BUTTON_PIN_BM (1 << BUTTON_PIN) // PD3

EpeeButton::EpeeButton()
{
    DDRD &= ~BUTTON_PIN_BM; // set pin 3 as input
    PORTD |= BUTTON_PIN_BM; // enable INPUT_PULLUP on pin 3
}

bool EpeeButton::isPressed() const
{
    return !(PIND & BUTTON_PIN_BM); // is inversed becaused of INPUT_PULLUP
}
