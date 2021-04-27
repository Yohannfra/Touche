/*
Touché Project
Copyright (C) 2021 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DebugLog.h"
#include "PlayerConfig.hpp"
#include "RGBLed.hpp"
#include "RadioModule.hpp"
#include "Timer.hpp"
#include "VirtualGround.hpp"
#include "WeaponButton.hpp"
#include "config.h"
#include "protocol.h"
#include "touche.h"
#include "utils.hpp"

#include <Arduino.h>

// Global classes
static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static WeaponButton weapon_button(EPEE_BUTTON_PIN);
static RGBLed led(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE);
static Timer timerHit;
static Timer timerButtonMaintened;
static PlayerConfig playerConfig(PLAYER_ROLE, DEFAULT_WEAPON_MODE);

// Config variables
static touche_role_e board_role;
static weapon_mode_e current_weapon;
static bool pisteMode = false;

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
#endif

    board_role = playerConfig.getRole();
    current_weapon = playerConfig.getWeapon();

    DEBUG_LOG_LN(board_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
    DEBUG_LOG_LN(current_weapon == EPEE ? "EPEE" : "FOIL");

    radio_module.init(board_role);

    led.blink(WEAPON_MODE_TO_COLOR(current_weapon), 1000, 1);
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    DEBUG_LOG_LN("Starting calibration");
    radio_module.sendMsg(CALIBRATION_STARTING, SERVER);

    while (virtualGround.calibrate() == false) {
        if (weapon_button.isPressed() == false) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(CALIBRATION_FAILED, SERVER);
            virtualGround.end_calibration(false);
            delay(500);
            return;
        }
    }
    DEBUG_LOG_LN("Calibration Done");
    virtualGround.end_calibration(true);
    radio_module.sendMsg(CALIBRATION_END, SERVER);
    delay(500);
}

void applyAckSettings(ack_payload_t ack)
{
    pisteMode = ack & ACK_PISTE_MODE;

    if (ack & ACK_EPEE) {
        current_weapon = EPEE;
    } else if (ack & ACK_FOIL) {
        current_weapon = FOIL;
    } else if (ack & ACK_SABRE) {
        // TODO
        // current_weapon = SABRE;
    }
}

void loop()
{
    if (weapon_button.isPressed()) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (!timerHit.isRunning()) {
            bool is_virtual_ground_triggered = virtualGround.trigger_ground();

            if (is_virtual_ground_triggered == false) {  // hit
                timerHit.start();
                led.setColor(RGB_LED_COLOR_GREEN);
                DEBUG_LOG_LN("== Sending Hit ==");
                ack_payload_t ack = radio_module.sendMsg(HIT, SERVER);
                applyAckSettings(ack);
            } else if (is_virtual_ground_triggered == true) {
                DEBUG_LOG_LN("== Virtual ground triggered ==");
                delay(100);
            }
        }

        if (timerButtonMaintened.isRunning() &&
            timerButtonMaintened.getTimeElapsed() > 2000 /* 2 secs */) {  // calibration
            run_calibration_process();
            led.turnOff();
            timerButtonMaintened.reset();
        }
    } else {  // button not pressed
        timerButtonMaintened.reset();

        if (timerHit.isRunning() && timerHit.getTimeElapsed() > FENCING_BLINKING_TIME) {  // reset
            led.turnOff();
            timerHit.reset();
            DEBUG_LOG_LN("Reset");
        }
    }
}
