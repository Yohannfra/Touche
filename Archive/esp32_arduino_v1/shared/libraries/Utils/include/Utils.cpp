#include <Arduino.h>
#include "constants.hpp"

void printDebugLog(const char *s)
{
    Serial.print(s);
}

void printDebugLog(const int n)
{
    Serial.print(n);
}

void printDebugLog(const float f)
{
    Serial.print(f);
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
