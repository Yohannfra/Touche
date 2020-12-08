#include <Arduino.h>

#include "Captouch.hpp"
#include "RadioModule.hpp"
#include "EpeeButton.hpp"
#include "Led.hpp"
#include "protocol.h"
#include "fencingConstants.h"
#include "board_id.h"
#include "DebugLog.hpp"
#include "utils.hpp"

Captouch captouch(4, 2);
RadioModule radio_module(7, 8);
EpeeButton epee_button;
Led led;

uint8_t device_id;

#define TIME_TO_ACTIVATE_CALIBRATION 3000
#define CALIBRATION_TIME 3000

unsigned long time_button_pressed_calibration = 0;
unsigned long time_button_pressed_delay = 0;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    while (!Serial) {
        // wait for serial
    }
    utils::print_board_infos();
#endif

    device_id = getBoardId();
    if (device_id == -1) {
        DEBUG_LOG_LN("Unknown Board ID");
        DEBUG_LOG_LN("Please add board id to BOARDS_IDS in board_id.cpp");
    }
    radio_module.init();
    led.blink(500);
}

void run_calibration_process()
{
    DEBUG_LOG_LN("Starting calibration");
    radio_module.sendMsg(device_id, CALIBRATION_STARTING_BIT_MASK);

    while (captouch.calibrate() == false) {
        if (epee_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(device_id, CALIBRATION_FAILED_BIT_MASK);
            captouch.end_calibration(false);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    // captouch.end_calibration(true);
    radio_module.sendMsg(device_id, CALIBRATION_END_BIT_MASK);
}

void loop()
{
    if (epee_button.isPressed()) {
        if (time_button_pressed_delay == 0 && !captouch.trigger_ground()) { // hit
            time_button_pressed_delay = millis();
            led.turnOn();
            DEBUG_LOG_LN("Sending Hit");
            radio_module.sendMsg(device_id, HIT_BIT_MASK);
        }

        if (millis() - time_button_pressed_delay > TIME_TO_ACTIVATE_CALIBRATION) { // calibration
            run_calibration_process();
            time_button_pressed_delay = 0;
        }
    }

    if (time_button_pressed_delay && !epee_button.isPressed() &&
                        millis() - time_button_pressed_delay > FENCING_BLINKING_TIME) { // reset
            led.turnOff();
            time_button_pressed_delay = 0;
    }
}