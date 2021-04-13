#include "DebugLog.h"
#include "WeaponButton.hpp"
#include "wsff.h"

WeaponButton::WeaponButton(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);
}

bool WeaponButton::isPressed() const
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
