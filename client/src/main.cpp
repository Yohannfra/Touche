/**
 * @file main.cpp
 * @brief wsff main file
 * @author Assouline Yohann
 * @date 2020-12-24
 */

#include <Arduino.h>

#include "VirtualGround.hpp"
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

#include "client_pinout.h"

static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static EpeeButton epee_button(EPEE_BUTTON_PIN);
static Led led(LED_PIN);
static Timer timerHit;
static Timer timerButtonMaintened;
static Timer timerForSleep;
static SleepManager sleepManager;

static device_id_t device_id;

#define TIME_TO_ACTIVATE_CALIBRATION 3000

#define TIME_BEFORE_SLEEP (5000UL * 60UL) // 5000 * 60 = 5 minutes

#ifdef WRITE_ID_TO_EEPROM
#define ID_TO_WRITE -1 // change value and add it to board_id.h
#endif

/**
 * @brief Arduino setup function
 */
void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    utils::print_board_infos();
#endif

#ifdef WRITE_ID_TO_EEPROM
#if (ID_TO_WRITE < 0)
#error "You must set id to a positive number"
#endif
    DEBUG_LOG_LN("Writing board id to eeprom");
    writeIdToEEPROM(ID_TO_WRITE);
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

    while (virtualGround.calibrate() == false) {
        if (epee_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(device_id, CALIBRATION_FAILED);
            virtualGround.end_calibration(false);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    virtualGround.end_calibration(true);
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

        if (!timerHit.isRunning() && !virtualGround.trigger_ground()) { // hit
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
