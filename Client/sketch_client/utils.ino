/*
** Assouline Yohann, 2020
** WSSF
** File description:
** utils for client
*/

#include "constants.hpp"

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
