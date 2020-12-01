#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include "protocol.h"

#define UNKNOWN_ID -1

#define PLAYER_1 0
#define PLAYER_2 1

class PlayerManager
{
private:
    int8_t _knowns_ids[2];
public:
    PlayerManager();
    int8_t getPlayerFromID(int8_t id) const;
    int8_t registerPlayer(int8_t id);
};
#endif /* PLAYERMANAGER_HPP */