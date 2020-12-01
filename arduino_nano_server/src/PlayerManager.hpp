#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include "protocol.h"

#define DEFAULT_ID -1

typedef enum {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    NOT_A_PLAYER = 2
}   player_index_e;

class PlayerManager
{
private:
    int8_t _knowns_ids[2];
public:
    PlayerManager();
    player_index_e getPlayerFromID(int8_t id) const;
    player_index_e registerPlayer(int8_t id);
};
#endif /* PLAYERMANAGER_HPP */