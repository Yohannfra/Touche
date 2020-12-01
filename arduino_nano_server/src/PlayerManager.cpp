#include "PlayerManager.hpp"
#include "DebugLog.hpp"
#include <Arduino.h>

PlayerManager::PlayerManager()
{
    _knowns_ids[PLAYER_1] = UNKNOWN_ID;
    _knowns_ids[PLAYER_2] = UNKNOWN_ID;
}

int8_t PlayerManager::getPlayerFromID(int8_t id) const
{
    if (_knowns_ids[PLAYER_1] == id)
        return PLAYER_1;
    else if (_knowns_ids[PLAYER_2] == id)
        return PLAYER_2;
    return UNKNOWN_ID;
}

int8_t PlayerManager::registerPlayer(int8_t id)
{
    if (_knowns_ids[PLAYER_1] == UNKNOWN_ID) {
        _knowns_ids[PLAYER_1] = id;
        return PLAYER_1;
    } else if (_knowns_ids[PLAYER_2] == UNKNOWN_ID) {
        _knowns_ids[PLAYER_2] = id;
        return PLAYER_2;
    } else {
        DEBUG_LOG_VAL("UNKNOWN ID: ", id);
        return UNKNOWN_ID;
    }
}