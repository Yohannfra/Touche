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

#include "ActionManager.hpp"
#include "ArduinoLog.h"
#include "Button.hpp"
#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"
#include "ServerConfig.hpp"
#include "config.h"
#include "protocol.h"
#include "touche.h"
#include "utils.hpp"

#include <Arduino.h>

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
ServerConfig config(DEFAULT_WEAPON_MODE);
static ActionManager action_manager;

void checkButtonsPressed();
void do_calib();

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

static bool is_calibrating = false;
uint32_t t1 = 0;

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        utils::print_packet(packet);

        touche_role_e player_role = GET_ROLE(packet);
        payload_type_e payload = GET_PAYLOAD(packet);

        if (payload & HIT) {
            Log.notice("HIT");
            action_manager.hit(player_role);
        } else if (payload & CALIBRATION_STARTING) {
            if (!is_calibrating) {
                Log.notice("CALIBRATION STARTED");
                t1 = millis();
                is_calibrating = true;
            } else {
                if (millis() - t1 > 200) {
                    do_calib();
                    t1 = millis();
                }
            }
        } else if (payload & CALIBRATION_END) {
            Log.notice("CALIBRATION END");
            led_ring.turn_off();
            led_ring.blink(GREEN_RGB, 100, 3);
        } else if (payload & CALIBRATION_FAILED) {
            Log.warning("CALIBRATION FAILED");
            led_ring.blink(RED_RGB, 100, 3);
        }
    }

    hit_type_e hit_type = action_manager.getHitStatus();

    if (hit_type != NO_HIT) {
        buzzer.play();
        led_ring.show_hits(hit_type);

        if (action_manager.isResetTime()) {
            Log.notice("resetting values");
            action_manager.reset();
            led_ring.turn_off();
            buzzer.stop();
        }
    } else {  // Check buttons only if no hit is occuring
        checkButtonsPressed();
    }
}
