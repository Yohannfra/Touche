/*
Touché Project
Copyright (C) 2024 Assouline Yohann

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

#include "ActionManager.hpp"
#include "ArduinoLog.h"
#include "Button.hpp"
#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "Potentiometer.hpp"
#include "RadioModule.hpp"
#include "ServerConfig.hpp"
#include "config.h"
#include "protocol.h"
#include "touche.h"
#include "utils.hpp"

#include <Arduino.h>

Buzzer buzzer(BUZZER_PIN);
Potentiometer potentiometer(POTENTIOMETER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
ServerConfig config(DEFAULT_WEAPON_MODE);
static ActionManager action_manager;

void checkButtonsPressed();
void runCalibrationProcess();

static bool is_calibrating = false;

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

    Log.trace(CRLF "==== Booting server ====" CRLF);

    Log.notice("%s", config.getWeapon() == EPEE ? "EPEE" : "FOIL");

    radio_module.init(SERVER);
    led_ring.init();
    led_ring.blink(ORANGE_RGB, 200, 1);

    radio_module.setAckPayload(CREATE_ACK_PAYLOAD(config.getPisteMode(), config.getWeapon()));
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        utils::print_packet(packet);

        touche_role_e player_role = GET_ROLE(packet);
        payload_type_e payload = GET_PAYLOAD(packet);

        if (payload == HIT) {
            Log.notice("HIT");
            action_manager.hit(player_role, true);
        } else if (payload == INVALID_HIT) {
            Log.notice("INVALID HIT");
            action_manager.hit(player_role, false);
        } else if (payload == CALIBRATION_STARTING) {
            Log.notice("CALIBRATION STARTED");
            is_calibrating = true;
            runCalibrationProcess();
        }

        if (payload == CALIBRATION_END) {
            Log.notice("CALIBRATION END");
            led_ring.do_circle_annimation(NONE_RGB);
            led_ring.blink(GREEN_RGB, 100, 3);
            is_calibrating = false;
        } else if (payload == CALIBRATION_FAILED) {
            Log.warning("CALIBRATION FAILED");
            led_ring.do_circle_annimation(NONE_RGB);
            led_ring.blink(RED_RGB, 100, 3);
            is_calibrating = false;
        }
    }

    // signal hit(s)
    uint16_t hits = action_manager.getHitStatus();

    if (hits != ActionManager::NONE) {
        buzzer.play(potentiometer.getMappedValue());
        led_ring.show_hits(hits);

        if (action_manager.isResetTime()) {
            Log.notice("resetting values");
            action_manager.reset();
            led_ring.turn_off();
            buzzer.stop();
        }
    } else {  // Check buttons only if no hit is occuring
        checkButtonsPressed();
    }

    if (is_calibrating) {
        runCalibrationProcess();
    }
}
