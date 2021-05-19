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

static void printLineEnding(Print *_logOutput)
{
    _logOutput->print(CRLF);
}

void setup()
{
#ifndef DISABLE_LOGGING
    Serial.begin(9600);

    // view available log level here : https://github.com/Yohannfra/Arduino-Log
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
    Log.setSuffix(printLineEnding);
#endif

    Log.trace(CRLF "==== Booting client ====" CRLF);

    board_role = playerConfig.getRole();
    current_weapon = playerConfig.getWeapon();

    Log.notice("Role: %s", board_role == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
    Log.notice("Weapon: %s", current_weapon == EPEE ? "EPEE" : "FOIL");

    radio_module.init(board_role);

    led.blink(RGBLed::WEAPON_MODE_TO_COLOR(current_weapon), 1000, 1);
}

/**
 * @brief do the calibration process.
 */
void run_calibration_process()
{
    Log.notice("== Starting calibration ==");
    radio_module.sendMsg(CALIBRATION_STARTING);

    while (virtualGround.calibrate() == false) {
        if (weapon.isHitting(current_weapon) == Weapon::NONE) {
            Log.warning("Button released during calibration");
            radio_module.sendMsg(CALIBRATION_FAILED);
            virtualGround.end_calibration(false);
            delay(500);
            return;
        }
    }
    Log.notice("== Calibration Done ==");
    virtualGround.end_calibration(true);
    radio_module.sendMsg(CALIBRATION_END);
    delay(500);
}

void applyAckSettings(ack_payload_t ack)
{
    weapon_mode_e tmp = current_weapon;

    if (ack == ACK_ERROR) {
        Log.warning("ack is ACK_ERROR");
        return;
    }

    utils::print_ack_payload(ack);

    pisteMode = ack & ACK_PISTE_MODE;

    if (ack & ACK_EPEE) {
        current_weapon = EPEE;
    } else if (ack & ACK_FOIL) {
        current_weapon = FOIL;
    } else if (ack & ACK_SABRE) {
        // current_weapon = SABRE;
    }

    if (tmp != current_weapon) {  // weapon changed, write it to EEPROM
        playerConfig.setWeapon(current_weapon);
    }
    Log.notice("Weapon is now : %s", current_weapon == FOIL ? "FOIL" : "EPEE");
    Log.notice("Piste is now : %s", pisteMode ? "Enabled" : "Disabled");
}

void loop()
{
    Weapon::hit_status_e hit_status = weapon.isHitting(current_weapon);

    if (hit_status != Weapon::NONE) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (hit_status == Weapon::VALID && !timerValidHit.isRunning()) {
            Log.notice("== Valid hit ==");
            timerValidHit.start();
            led.setColor(RGBLed::GREEN);
            ack_payload_t ack = radio_module.sendMsg(HIT);
            applyAckSettings(ack);
            timerInvalidHit.reset();
        } else if (!timerInvalidHit.isRunning() && !timerValidHit.isRunning()) {  // INVALID HIT
            Log.notice("== Invalid hit ==");
            timerInvalidHit.start();
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
            Log.notice("Reset");
            led.turnOff();
            timerValidHit.reset();
            timerInvalidHit.reset();
        }
    }
}
