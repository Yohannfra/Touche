#include <Arduino.h>
#include "Captouch.hpp"
#include "RadioModule.hpp"

#include "protocol.h"
#include "fencingConstants.h"
#include "id.h"

#define BUTTON_PIN 3
#define LED_PIN 5

Captouch captouch(4, 2);
RadioModule radio_module;

device_id_t id = TO_ID(CLIENT_ID);

unsigned long time_button_pressed_calibration = 0;
unsigned long time_button_pressed_delay = 0;

void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(0));

    id = TO_ID(random(1000)); // FIXME DIRTY TRICK   < ------

    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    radio_module.init();

    // blink on boot
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
            radio_module.sendMsg(id, HIT);
        }
    }
    if (time_button_pressed_delay && millis() - time_button_pressed_delay > 1000 /* 1 second */) {
            digitalWrite(LED_PIN, LOW);
            time_button_pressed_delay = 0;
    }

    //     if (time_button_pressed_calibration == 0) {
    //         time_button_pressed_calibration = millis();
    //     } else if (millis() - time_button_pressed_calibration > 5000 /* 5 seconds */) {
    //         captouch.calibrate();
    //         // send calibration ok signal
    //     }
    // } else {
    //     time_button_pressed_calibration = 0;
    // }

    if (captouch.trigger_ground()) {
        // TODO : send ground
    }
}