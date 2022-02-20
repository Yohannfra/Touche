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
#include "Button.hpp"
#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "Potentiometer.hpp"
#include "RadioModule.hpp"
#include "ServerConfig.hpp"

#include <Arduino.h>

extern Buzzer buzzer;
extern Potentiometer potentiometer;
extern LedRing led_ring;
extern RadioModule radio_module;
extern ServerConfig config;

static Button buttonPisteMode(PIN_BUTTON_PISTE_MODE);
static Button buttonSwitchPlayer(PIN_BUTTON_SWITCH_PLAYERS);
static Button buttonChangeWeapon(PIN_BUTTON_CHANGE_WEAPON);

void checkButtonsPressed()
{
    // Piste mode
    if (buttonPisteMode.isPressed()) {
        Log.notice("Button piste pressed !");
        config.setPisteMode(!config.getPisteMode());
        radio_module.setAckPayload(CREATE_ACK_PAYLOAD(config.getPisteMode(), config.getWeapon()));
        buzzer.play(potentiometer.getMappedValue());
        led_ring.blink(ORANGE_RGB, 100, 3);
        buzzer.stop();
    }

    // switch players
    if (buttonSwitchPlayer.isPressed()) {
        Log.notice("Button switch pressed !");
        led_ring.switchColors();
        buzzer.play(potentiometer.getMappedValue());
        led_ring.blinkBoth(led_ring.getPlayerColor(PLAYER_1), led_ring.getPlayerColor(PLAYER_2), 400, 2);
        buzzer.stop();
    }

    // change weapon
    if (buttonChangeWeapon.isPressed()) {
        Log.notice("Button change weapon pressed !");

        constexpr uint8_t NB_WEAPONS = 2;
        const weapon_mode_e weapons[NB_WEAPONS] = {EPEE, FOIL /*, SABRE */};
        config.setWeapon(weapons[(config.getWeapon() + 1) % NB_WEAPONS]);  // shift to next weapon
        radio_module.setAckPayload(CREATE_ACK_PAYLOAD(config.getPisteMode(), config.getWeapon()));

        Log.notice("weapon is now: %s", config.getWeapon() == EPEE ? "EPEE" : "FOIL");

        buzzer.play(potentiometer.getMappedValue());
        led_ring.blink(ORANGE_RGB, 100, 3);
        buzzer.stop();
    }
}