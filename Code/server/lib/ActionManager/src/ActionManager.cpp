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
#include "touche.h"

#include <Arduino.h>

ActionManager::ActionManager()
{
    this->reset();
}

void ActionManager::reset()
{
    _time_last_hit = 0;
    _player_actions[PLAYER_1] = NONE;
    _player_actions[PLAYER_2] = NONE;
}

bool ActionManager::isResetTime() const
{
    return _time_last_hit && millis() - _time_last_hit > FENCING_BLINKING_TIME;
}

void ActionManager::hit(touche_role_e role, bool valid)
{
    int64_t current_time = millis();

    if (_time_last_hit == 0) {  // first hit
        _time_last_hit = millis();
        _player_actions[role] = valid ? VALID_HIT : INVALID_HIT;
    } else {  // maybe double hit
        Log.verbose("Checking double touch ...");
        Log.verbose("Lap is %l", current_time - _time_last_hit);
        if (current_time - _time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            Log.notice("DOUBLE HIT!");
            _player_actions[role] = valid ? VALID_HIT : INVALID_HIT;
        }
    }
}

uint16_t ActionManager::getHitStatus() const
{
    uint16_t ret = 0;

    ret |= (_player_actions[PLAYER_1] << 8);
    ret |= _player_actions[PLAYER_2];

    return ret;
}
