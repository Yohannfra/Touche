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

static Buzzer buzzer(BUZZER_PIN);
static LedRing led_ring(LED_RING_PIN);
static RadioModule radio_module(NRF24L01_CE_PIN, NRF24L01_CS_PIN);
static ActionManager action_manager;

static Button buttonPisteMode(PIN_BUTTON_PISTE_MODE);
static Button buttonSwitchPlayer(PIN_BUTTON_SWITCH_PLAYERS);
static Button buttonChangeWeapon(PIN_BUTTON_CHANGE_WEAPON);
static ServerConfig serverConfig(DEFAULT_WEAPON_MODE);

static bool pisteMode = false;
static weapon_mode_e current_weapon;

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

    Log.notice(CRLF "==== Booting ====");

    current_weapon = serverConfig.getWeapon();
    Log.notice("%s", current_weapon == EPEE ? "EPEE" : "FOIL");

    radio_module.init(SERVER);
    led_ring.init();
    led_ring.blink(ORANGE_RGB, 200, 1);

    radio_module.setAckPayload(CREATE_ACK_PAYLOAD(false, current_weapon));
}

void checkButtonsPressed()  // TODO
{
    // Piste mode
    if (buttonPisteMode.isPressed()) {
        Log.notice("Button piste pressed !");
        pisteMode = !pisteMode;
        radio_module.sendMsg(pisteMode ? ENABLE_PISTE_MODE : DISABLE_PISTE_MODE, PLAYER_1);
        radio_module.sendMsg(pisteMode ? ENABLE_PISTE_MODE : DISABLE_PISTE_MODE, PLAYER_2);
        delay(1000);
    }

    // switch players
    if (buttonSwitchPlayer.isPressed()) {
        Log.notice("Button switch pressed !");
        led_ring.switchColors();
        led_ring.blinkBoth(led_ring.getPlayerColor(PLAYER_1), led_ring.getPlayerColor(PLAYER_2), 400, 2);
        delay(1000);
    }

    // change weapon
    if (buttonChangeWeapon.isPressed()) {
        const weapon_mode_e weapons[3] = {EPEE, FOIL /*, SABRE */};
        current_weapon = weapons[(current_weapon + 1) % 2];  // shift to next weapon

        Log.notice("Button change weapon pressed !");
        Log.notice("weapon is now: %s", current_weapon == EPEE ? "EPEE" : "FOIL");

        delay(1000);
    }
}

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
            Log.notice("CALIBRATION STARTED");
            for (size_t i = 0; i < 2 * 4; i++) {
                led_ring.do_circle_annimation(ORANGE_RGB, i);
                packet_t p = radio_module.receiveMsg();
                if (p) {
                    break;
                }
            }
            led_ring.turn_off();
        } else if (payload & CALIBRATION_END) {
            Log.notice("CALIBRATION END");
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
