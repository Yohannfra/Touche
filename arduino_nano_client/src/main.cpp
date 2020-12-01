#include <Arduino.h>

#include "Captouch.hpp"
#include "RadioModule.hpp"

#include "protocol.h"
#include "fencingConstants.h"
#include "board_id.h"

#define BUTTON_PIN 3
#define LED_PIN 5

Captouch captouch(4, 2);
RadioModule radio_module;

uint8_t device_id;

unsigned long time_button_pressed_calibration = 0;
unsigned long time_button_pressed_delay = 0;

void setup()
{
    Serial.begin(9600);

    device_id = getBoardId();
    if (device_id == -1) {
        Serial.println("Unknown Board ID");
        Serial.println("Please add board id to BOARDS_IDS in board_id.cpp");
    }

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
            radio_module.sendMsg(device_id, HIT_BIT_MASK);
        }
    }
    if (time_button_pressed_delay && millis() - time_button_pressed_delay > 1000) {
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

    // if (captouch.trigger_ground()) { // Fait bugger le button wtf
        // TODO : send ground
    // }
}