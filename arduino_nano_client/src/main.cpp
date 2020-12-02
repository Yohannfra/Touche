#include <Arduino.h>

#include "Captouch.hpp"
#include "RadioModule.hpp"
#include "EpeeButton.hpp"
#include "Led.hpp"
#include "protocol.h"
#include "fencingConstants.h"
#include "board_id.h"
#include "DebugLog.hpp"

#define BUTTON_PIN 3
#define LED_PIN 5

Captouch captouch(4, 2);
RadioModule radio_module(7, 8);
EpeeButton epee_button(BUTTON_PIN);
Led led(LED_PIN);

uint8_t device_id;

unsigned long time_button_pressed_calibration = 0;
unsigned long time_button_pressed_delay = 0;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    while (!Serial) {
        // wait for serial
    }
#endif

    device_id = getBoardId();
    if (device_id == -1) {
        DEBUG_LOG_LN("Unknown Board ID");
        DEBUG_LOG_LN("Please add board id to BOARDS_IDS in board_id.cpp");
    }
    radio_module.init();
    led.blink(1000);
}

void loop()
{
    if (epee_button.isPressed()) {
        if (time_button_pressed_delay == 0) {
            time_button_pressed_delay = millis();
            led.turnOn();
            radio_module.sendMsg(device_id, HIT_BIT_MASK);
        }
    }

    if (time_button_pressed_delay && millis() - time_button_pressed_delay > 1000) {
            led.turnOff();
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