#include <Arduino.h>

#include "VirtualGround.hpp"
#include "RadioModule.hpp"
#include "EpeeButton.hpp"
#include "Led.hpp"
#include "protocol.h"
#include "fencingConstants.h"
#include "ClientRole.hpp"
#include "DebugLog.hpp"
#include "utils.hpp"
#include "Timer.hpp"
#include "SleepManager.hpp"

#include "client_config.h"

static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static EpeeButton epee_button(EPEE_BUTTON_PIN);
static Led led(LED_PIN);
static Timer timerHit;
static Timer timerButtonMaintened;
static Timer timerForSleep;

static wsff_role_e BOARD_ROLE;

#define TIME_TO_ACTIVATE_CALIBRATION 3000

#define TIME_BEFORE_SLEEP (5000UL * 60UL) // 5000 * 60 = 5 minutes

#ifdef WRITE_ROLE_TO_EEPROM
#define ROLE_TO_WRITE PLAYER_2 // change value and add it to board_id.h
#endif

/**
 * @brief Arduino setup function
 */
void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    DEBUG_LOG_LN(getBoardRole() == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
#endif

#ifdef WRITE_ROLE_TO_EEPROM
    #if (ROLE_TO_WRITE != PLAYER_1 && ROLE_TO_WRITE != PLAYER_2)
        #error "ROLE_TO_WRITE must bo PLAYER_1 or PLAYER_2"
    #endif
    DEBUG_LOG_LN("Writing board id to eeprom");
    writeRoleToEEPROM(ROLE_TO_WRITE);
    DEBUG_LOG_LN("Now flash the board with the normal firmware");
    led.turnOn();
    while (1) {}
#endif

    BOARD_ROLE = getBoardRole();
    radio_module.init(BOARD_ROLE);
    led.blink(500);
    timerForSleep.start();
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    DEBUG_LOG_LN("Starting calibration");
    radio_module.sendMsg(BOARD_ROLE, CALIBRATION_STARTING);

    while (virtualGround.calibrate() == false) {
        if (epee_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(BOARD_ROLE, CALIBRATION_FAILED);
            virtualGround.end_calibration(false);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    virtualGround.end_calibration(true);
    radio_module.sendMsg(BOARD_ROLE, CALIBRATION_END);
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
            radio_module.sendMsg(BOARD_ROLE, HIT);
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
        SleepManager::sleep();
        timerForSleep.start();
    }
}
