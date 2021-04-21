/*
WSFF Project
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

#include <Arduino.h>
#include "ActionManager.hpp"
#include "wsff.h"
#include "DebugLog.h"

ActionManager::ActionManager()
{
    this->reset();
}

void ActionManager::reset()
{
    _time_last_hit = 0;
    _player_actions[PLAYER_1] = NO_ACTION;
    _player_actions[PLAYER_2] = NO_ACTION;
}

bool ActionManager::isResetTime() const
{
    return _time_last_hit && millis() - _time_last_hit > FENCING_BLINKING_TIME;
}

void ActionManager::hit(wsff_role_e role)
{
    int64_t current_time = millis();

    if (_time_last_hit == 0) { // first hit
        _time_last_hit = millis();
        _player_actions[role] = ACTION_HIT;
    } else { // maybe double hit
        if (current_time - _time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            _player_actions[role] = ACTION_HIT;
        }
    }
}

hit_type_e ActionManager::getHitStatus() const
{
    if (_player_actions[PLAYER_1] == ACTION_HIT && _player_actions[PLAYER_2] == ACTION_HIT)
        return DOUBLE_HIT;
    else if (_player_actions[PLAYER_1] == ACTION_HIT)
        return HIT_PLAYER_1;
    else if (_player_actions[PLAYER_2] == ACTION_HIT)
        return HIT_PLAYER_2;
    return NO_HIT;
}
