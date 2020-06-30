#include <Arduino.h>
#include "constants.hpp"

void printDebugLog(const char *s)
{
#ifdef DEBUG
    Serial.print(s)
#endif
}

void blinkLed(byte pin)
{
    digitalWrite(pin, HIGH);
    delay(FENCING_BLINKING_TIME);
    digitalWrite(pin, LOW);
}

void handleError()
{
    printDebugLog("FATAL ERROR");
    while (1) {  }
}

void setupSerial(unsigned int baudRate)
{
    Serial.begin(baudRate);
    while (!Serial)  {
        // wait for serial to start
    }
}
