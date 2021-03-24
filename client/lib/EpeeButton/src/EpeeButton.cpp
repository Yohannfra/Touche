#include "DebugLog.h"
#include "EpeeButton.hpp"
#include "wsff.h"

EpeeButton::EpeeButton(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

bool EpeeButton::isPressed() const
{
    bool state = !digitalRead(_pin);

    if (state) {
        unsigned long t1 = millis();

        while (!digitalRead(_pin) == state) {
            if (millis() - t1 > FENCING_MINIMUM_TIME_VALID_HIT) {
                // DEBUG_LOG_LN("EPEE BTN PRESSED");
                return true;
            }
        }
    }
    return false;
}
