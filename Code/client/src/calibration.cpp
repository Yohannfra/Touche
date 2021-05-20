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
#include "RadioModule.hpp"
#include "VirtualGround.hpp"
#include "Weapon.hpp"
#include "protocol.h"
#include "touche.h"
#include "utils.hpp"

#include <Arduino.h>

extern VirtualGround virtualGround;
extern RadioModule radio_module;
extern PlayerConfig config;
extern Weapon weapon;

void run_calibration_process()
{
    Log.notice("== Starting calibration ==");
    radio_module.sendMsg(CALIBRATION_STARTING);

    while (virtualGround.calibrate() == false) {
        if (weapon.isHitting(config.getWeapon()) == Weapon::NONE) {
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
