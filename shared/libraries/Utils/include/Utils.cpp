#include <Arduino.h>
#include "constants.hpp"

void printDebugLog(const char *s)
{
#ifdef DEBUG
    Serial.print(s)
#endif
}

void printDebugLog(const int n)
{
#ifdef DEBUG
    Serial.print(n)
#endif
}

void printDebugLog(const float f)
{
#ifdef DEBUG
    Serial.print(f)
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
