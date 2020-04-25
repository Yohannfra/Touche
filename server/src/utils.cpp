#include <Arduino.h>
#include "constants.hpp"

void blink_led(byte pin)
{
    digitalWrite(pin, HIGH);
    delay(FENCING_BLINKING_TIME);
    digitalWrite(pin, LOW);
}
