#include "constants.hpp"
#include <Arduino.h>

void blink_led(byte pin)
{
    digitalWrite(pin, HIGH);
    delay(FENCING_BLINKING_TIME);
    digitalWrite(pin, LOW);
}

void handle_error()
{
    Serial.println("FATAL ERROR");
    while (1) {  }
}
