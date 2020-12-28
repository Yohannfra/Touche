/**
 * @file main.cpp
 * @brief wsff main file
 * @author Assouline Yohann
 * @date 2020-12-24
 */

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
#include "Timer.hpp"
#include "SleepManager.hpp"

static Captouch captouch(4, 2);
static RadioModule radio_module(7, 8);
static EpeeButton epee_button(3);
static Led led(5);
static Timer timerHit;
static Timer timerButtonMaintened;
static Timer timerForSleep;
static SleepManager sleepManager;

static device_id_t device_id;

#define TIME_TO_ACTIVATE_CALIBRATION 3000

#define TIME_BEFORE_SLEEP (5000UL * 60UL) // 5000 * 60 = 5 minutes

/**
 * @brief Arduino setup function
 */
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
    if (device_id == 0) {
        DEBUG_LOG_LN("Unknown Board ID");
        DEBUG_LOG_LN("Please add board id to BOARDS_IDS in board_id.cpp");
    }
    radio_module.init();
    led.blink(500);
    timerForSleep.start();
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    DEBUG_LOG_LN("Starting calibration");
    radio_module.sendMsg(device_id, CALIBRATION_STARTING);

    while (captouch.calibrate() == false) {
        if (epee_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(device_id, CALIBRATION_FAILED);
            captouch.end_calibration(false);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    captouch.end_calibration(true);
    radio_module.sendMsg(device_id, CALIBRATION_END);
}

/**
 * @brief Arduino loop function
 */
void loop()
{
    if (epee_button.isPressed()) {
        timerForSleep.start();

        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (!timerHit.isRunning() && !captouch.trigger_ground()) { // hit
            timerHit.start();
            led.turnOn();
            DEBUG_LOG_LN("Sending Hit");
            radio_module.sendMsg(device_id, HIT);
        }

        if (timerButtonMaintened.isRunning() &&
                timerButtonMaintened.getTimeElapsed() > TIME_TO_ACTIVATE_CALIBRATION) { // calibration
            run_calibration_process();
            led.turnOff();
            timerButtonMaintened.reset();
        }
    } else { // button not pressed
        timerButtonMaintened.reset();

        if (timerHit.isRunning() && timerHit.getTimeElapsed() > FENCING_BLINKING_TIME) { // reset
            led.turnOff();
            timerHit.reset();
        }
    }

    // if unused for more than 5 mins go to sleep
    if (timerForSleep.isRunning() && timerForSleep.getTimeElapsed() > TIME_BEFORE_SLEEP) {
        led.turnOff();
        sleepManager.sleep();
        timerForSleep.start();
    }
}
