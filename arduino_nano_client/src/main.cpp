#include <Arduino.h>
#include "Captouch.hpp"

#define BUTTON_PIN 3
#define LED_PIN 5

Captouch captouch(4, 2);

unsigned long time_button_pressed_calibration = 0;
unsigned long time_button_pressed_delay = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

void loop()
{
    if (digitalRead(BUTTON_PIN)) {
        if (time_button_pressed_delay == 0) {
            time_button_pressed_delay = millis();
            digitalWrite(LED_PIN, HIGH);
            // send hit
        } else if (millis() - time_button_pressed_delay > 1000 /* 1 second */) {
            digitalWrite(LED_PIN, LOW);
            time_button_pressed_delay = 0;
        }

        if (time_button_pressed_calibration == 0) {
            time_button_pressed_calibration = millis();
        } else if (millis() - time_button_pressed_calibration > 5000 /* 5 seconds */) {
            captouch.calibrate();
            // send calibration ok signal
        }
    } else {
        time_button_pressed_calibration = 0;
    }

    if (captouch.trigger_ground()) {
        // send ground
    }
}