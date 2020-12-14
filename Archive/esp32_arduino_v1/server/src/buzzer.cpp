#include <Arduino.h>
#include "server.hpp"

void playBuzzer(bool state)
{
#ifndef DEBUG
    digitalWrite(BUZZER_PIN, state);
#endif
}