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
VirtualGround virtualGround(VIRTUAL_PIN_OUT, VIRTUAL_PIN_IN);
RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
Weapon weapon(EPEE_BUTTON_PIN, virtualGround);
static RGBLed led(LED_PIN_RED, LED_PIN_GREEN, LED_PIN_BLUE);
static Timer timerValidHit;
static Timer timerInvalidHit;
static Timer timerButtonMaintened;
PlayerConfig config(PLAYER_ROLE, DEFAULT_WEAPON_MODE);

void run_calibration_process();

/**
 * @brief callback needed for arduino-log
 */
static void printLineEnding(Print *_logOutput)
{
    _logOutput->print(CRLF);
}

void setup()
{
#ifndef DISABLE_LOGGING
    Serial.flush();
    Serial.begin(9600);

    // view available log level here : https://github.com/Yohannfra/Arduino-Log
    Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
    Log.setSuffix(printLineEnding);
#endif

    Log.trace(CRLF "==== Booting client ====" CRLF);

    Log.notice("Role: %s", config.getRole() == PLAYER_1 ? "PLAYER_1" : "PLAYER_2");
    Log.notice("Weapon: %s", config.getWeapon() == EPEE ? "EPEE" : "FOIL");

    radio_module.init(config.getRole());

    led.blink(RGBLed::WEAPON_MODE_TO_COLOR(config.getWeapon()), 1000, 1);
}

static void applyAckSettings(ack_payload_t ack)
{
    if (ack == ACK_ERROR) {
        Log.warning("ack is ACK_ERROR");
        return;
    }

    utils::print_ack_payload(ack);

    config.setPisteMode(ack & ACK_PISTE_MODE);

    if (ack & ACK_EPEE && config.getWeapon() != EPEE) {
        config.setWeapon(EPEE);
        virtualGround.reset();
    } else if (ack & ACK_FOIL && config.getWeapon() != FOIL) {
        config.setWeapon(FOIL);
        virtualGround.reset();
    } else if (ack & ACK_SABRE) {
        // config.setWeapon(SABRE);
    }

    Log.notice("Weapon is now : %s", config.getWeapon() == FOIL ? "FOIL" : "EPEE");
    Log.notice("Piste is now : %s", config.getPisteMode() ? "Enabled" : "Disabled");
}

void loop()
{
    Weapon::hit_status_e hit_status = weapon.isHitting(config.getWeapon());

    if (hit_status != Weapon::NONE) {
        if (!timerButtonMaintened.isRunning()) {
            timerButtonMaintened.start();
        }

        if (hit_status == Weapon::VALID && !timerValidHit.isRunning()) {
            Log.notice("== Valid hit ==");
            timerValidHit.start();
            led.setColor(RGBLed::GREEN);
            applyAckSettings(radio_module.sendMsg(HIT));
            timerInvalidHit.reset();
        } else if (!timerInvalidHit.isRunning() && !timerValidHit.isRunning()) {  // INVALID HIT
            Log.notice("== Invalid hit ==");
            if (config.getWeapon() == FOIL) {
                applyAckSettings(radio_module.sendMsg(INVALID_HIT));
            }
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
