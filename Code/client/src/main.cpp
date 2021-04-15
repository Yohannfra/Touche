#include <Arduino.h>

#include "VirtualGround.hpp"
#include "RadioModule.hpp"
#include "WeaponButton.hpp"
#include "RGBLed.hpp"
#include "protocol.h"
#include "wsff.h"
#include "DebugLog.h"
#include "utils.hpp"
#include "Timer.hpp"
#include "PlayerConfig.hpp"

#include "config.h"

// Global classes
static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static WeaponButton weapon_button(EPEE_BUTTON_PIN);
static RGBLed led(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE);
static Timer timerHit;
static Timer timerButtonMaintened;
static PlayerConfig playerConfig(PLAYER_ROLE, DEFAULT_WEAPON_MODE);

// Config variables
static wsff_role_e board_role;
static weapon_mode_e weapon_mode;
/* static bool pisteMode = false; */

void wait_for_server_instructions()
{
    led.setColor(COLOR_LISTEN_TO_SERVER_MODE);
    delay(1000);

    // init nrf ...
    while (1) {
        if (weapon_button.isPressed()) {
            break;
        }
    }
    led.turnOff();
    // deinit nrf ...
}

void setup()
{
    #ifdef DEBUG
        Serial.begin(9600);
    #endif

    board_role = playerConfig.getRole();
    weapon_mode = playerConfig.getWeapon();

    DEBUG_LOG_LN(board_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
    DEBUG_LOG_LN(weapon_mode == EPEE ? "EPEE": "FOIL");

    radio_module.init(board_role);

    if (weapon_button.isPressed()) {
        wait_for_server_instructions();
    }
    led.blink(WEAPON_MODE_TO_COLOR(weapon_mode), 1000, 1);
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    DEBUG_LOG_LN("Starting calibration");
    radio_module.sendMsg(board_role, CALIBRATION_STARTING);

    while (virtualGround.calibrate() == false) {
        if (weapon_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(board_role, CALIBRATION_FAILED);
            virtualGround.end_calibration(false);
            delay(500);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    virtualGround.end_calibration(true);
    radio_module.sendMsg(board_role, CALIBRATION_END);
    delay(500);
}

/**
 * @brief Arduino loop function
 */
void loop()
{
    if (weapon_button.isPressed()) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (!timerHit.isRunning()) {
            bool is_virtual_ground_triggered = virtualGround.trigger_ground();

            if (is_virtual_ground_triggered == false) { // hit
                timerHit.start();
                led.setColor(RGB_LED_COLOR_GREEN);
                DEBUG_LOG_LN("== Sending Hit ==");
                radio_module.sendMsg(board_role, HIT);
            } else if (is_virtual_ground_triggered == true) {
                DEBUG_LOG_LN("== Virtual ground triggered ==");
                delay(100);
            }
        }

        if (timerButtonMaintened.isRunning() &&
                timerButtonMaintened.getTimeElapsed() > 2000 /* 2 secs */) { // calibration
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
