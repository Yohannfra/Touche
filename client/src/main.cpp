#include <Arduino.h>

#include "VirtualGround.hpp"
#include "RadioModule.hpp"
#include "EpeeButton.hpp"
#include "Led.hpp"
#include "protocol.h"
#include "wsff.h"
#include "ClientRole.hpp"
#include "DebugLog.h"
#include "utils.hpp"
#include "Timer.hpp"

#include "client_config.h"

static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static EpeeButton epee_button(EPEE_BUTTON_PIN);
static Led led(LED_PIN);
static Timer timerHit;
static Timer timerButtonMaintened;

static wsff_role_e BOARD_ROLE;

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
            delay(500);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    virtualGround.end_calibration(true);
    radio_module.sendMsg(BOARD_ROLE, CALIBRATION_END);
    delay(500);
}

/**
 * @brief Arduino loop function
 */
void loop()
{
    if (epee_button.isPressed()) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (!timerHit.isRunning()) {
            bool is_virtual_ground_triggered = virtualGround.trigger_ground();

            if (is_virtual_ground_triggered == false) { // hit
                timerHit.start();
                led.turnOn();
                DEBUG_LOG_LN("== Sending Hit ==");
                radio_module.sendMsg(BOARD_ROLE, HIT);
            } else if (is_virtual_ground_triggered == true) {
                DEBUG_LOG_LN("== Virtual ground triggered ==");
                delay(100);
            }
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
            DEBUG_LOG_LN("Reset");
        }
    }
}
