#include <Arduino.h>
#include <CapacitiveSensor.h>

#define BUTTON_PIN 3
#define LED_PIN 5

CapacitiveSensor captouch = CapacitiveSensor(4,2);

#define TOUCHVAL_THREESHOLD 50000 // change me

void setup()
{
    Serial.begin(9600);

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    captouch.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate

    // end of init
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);

}

void loop()
{
    if (digitalRead(BUTTON_PIN)) {
        digitalWrite(LED_PIN, HIGH);
        delay(1000);
        digitalWrite(LED_PIN, LOW);
    }
    long touchval =  captouch.capacitiveSensorRaw(1);
    if (touchval > TOUCHVAL_THREESHOLD) {
        // send ground
    }
    // Serial.println(touchval);
}