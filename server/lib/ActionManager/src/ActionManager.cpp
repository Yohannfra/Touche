#include <Arduino.h>
#include "ActionManager.hpp"
#include "fencingConstants.h"
#include "DebugLog.hpp"

ActionManager::ActionManager()
{
    _time_last_hit = 0;
    _player_actions[PLAYER_1] = NO_ACTION;
    _player_actions[PLAYER_2] = NO_ACTION;
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

void ActionManager::hit(player_index_e index)
{
    int64_t current_time = millis();

    if (_time_last_hit == 0) { // first hit
        _time_last_hit = millis();
        _player_actions[index] = ACTION_HIT;
    } else { // maybe double hit
        if (current_time - _time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            _player_actions[index] = ACTION_HIT;
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