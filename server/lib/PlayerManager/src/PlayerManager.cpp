#include "PlayerManager.hpp"
#include "DebugLog.hpp"
#include <Arduino.h>

PlayerManager::PlayerManager()
{
    _knowns_ids[PLAYER_1] = DEFAULT_ID;
    _knowns_ids[PLAYER_2] = DEFAULT_ID;
    _player_count = 0;
}

player_index_e PlayerManager::getPlayerFromID(int8_t id) const
{
    if (_knowns_ids[PLAYER_1] == id)
        return PLAYER_1;
    else if (_knowns_ids[PLAYER_2] == id)
        return PLAYER_2;
    return NOT_A_PLAYER;
}

player_index_e PlayerManager::registerPlayer(int8_t id)
{
    if (_knowns_ids[PLAYER_1] == DEFAULT_ID) {
        DEBUG_LOG_VAL("Registering player 1 with id", id);
        _knowns_ids[PLAYER_1] = id;
        _player_count += 1;
        return PLAYER_1;
    } else if (_knowns_ids[PLAYER_2] == DEFAULT_ID) {
        DEBUG_LOG_VAL("Registering player 2 with id", id);
        _knowns_ids[PLAYER_2] = id;
        _player_count += 1;
        return PLAYER_2;
    } else {
        DEBUG_LOG_VAL("UNKNOWN ID: ", id);
        return NOT_A_PLAYER;
    }
}

uint8_t PlayerManager::getPlayerCount() const
{
    return _player_count;
}