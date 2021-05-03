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
#include "ArduinoLog.h"
#include "DebugLog.h"
#include "PlayerConfig.hpp"
#include "RGBLed.hpp"
#include "RadioModule.hpp"
#include "Timer.hpp"
#include "VirtualGround.hpp"
#include "Weapon.hpp"
#include "config.h"
#include "protocol.h"
#include "touche.h"
#include "utils.hpp"

#include <Arduino.h>

// Global classes
static VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static Weapon weapon(EPEE_BUTTON_PIN, virtualGround);
static RGBLed led(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE);
static Timer timerValidHit;
static Timer timerInvalidHit;
static Timer timerButtonMaintened;
static PlayerConfig playerConfig(PLAYER_ROLE, DEFAULT_WEAPON_MODE);

// Config variables
static touche_role_e board_role;
static weapon_mode_e current_weapon;
static bool pisteMode = false;

void setup()
{
#ifndef DISABLE_LOGGING
    Serial.begin(9600);

    /* set log level
    * 0 - LOG_LEVEL_SILENT     no output
    * 1 - LOG_LEVEL_FATAL      fatal errors
    * 2 - LOG_LEVEL_ERROR      all errors
    * 3 - LOG_LEVEL_WARNING    errors, and warnings
    * 4 - LOG_LEVEL_NOTICE     errors, warnings and notices
    * 5 - LOG_LEVEL_TRACE      errors, warnings, notices & traces
    * 6 - LOG_LEVEL_VERBOSE    all
    */
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
#endif

    board_role = playerConfig.getRole();
    current_weapon = playerConfig.getWeapon();

    Log.notice("Role: %s\r\n", board_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
    Log.notice("Weapon: %s\r\n", current_weapon == EPEE ? "EPEE" : "FOIL");

    radio_module.init(board_role);

    led.blink(RGBLed::WEAPON_MODE_TO_COLOR(current_weapon), 1000, 1);
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    DEBUG_LOG_LN("== Starting calibration ==");
    radio_module.sendMsg(CALIBRATION_STARTING, SERVER);

    while (virtualGround.calibrate() == false) {
        if (weapon.isHitting(current_weapon) == Weapon::NONE) {
            DEBUG_LOG_LN("Button released during calibration");
            radio_module.sendMsg(CALIBRATION_FAILED, SERVER);
            virtualGround.end_calibration(false);
            delay(500);
            return;
        }
    }
    DEBUG_LOG_LN("== Calibration Done ==");
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
    DEBUG_LOG_VAL("Weapon is : ", current_weapon == FOIL ? "FOIL" : "EPEE");
    DEBUG_LOG_VAL("Piste is : ", pisteMode ? "Enabled" : "Disabled");
}

void loop()
{
    Weapon::hit_status_e hit_status = weapon.isHitting(current_weapon);

    if (hit_status != Weapon::NONE) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (hit_status == Weapon::VALID && !timerValidHit.isRunning()) {
            timerValidHit.start();
            led.setColor(RGBLed::GREEN);
            DEBUG_LOG_LN("== Valid hit ==");
            ack_payload_t ack = radio_module.sendMsg(HIT, SERVER);
            applyAckSettings(ack);
            timerInvalidHit.reset();
        } else if (!timerInvalidHit.isRunning() && !timerValidHit.isRunning()) {  // INVALID HIT
            DEBUG_LOG_LN("== Invalid hit ==");
            led.setColor(RGBLed::RED);
        }

        if (timerButtonMaintened.isRunning() &&
            timerButtonMaintened.getTimeElapsed() > 2000 /* 2 secs */) {  // calibration
            run_calibration_process();
            timerButtonMaintened.reset();
        }
    } else {  // No hit occuring
        timerButtonMaintened.reset();

        if (timerValidHit.getTimeElapsed() > FENCING_BLINKING_TIME ||
            timerInvalidHit.getTimeElapsed() > FENCING_BLINKING_TIME) {  // reset all
            DEBUG_LOG_LN("Reset");
            led.turnOff();
            timerValidHit.reset();
            timerInvalidHit.reset();
        }
    }
}
