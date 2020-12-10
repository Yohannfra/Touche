#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <stdint.h>
#include "PlayerManager.hpp"

typedef enum {
    HIT_PLAYER_1,
    HIT_PLAYER_2,
    DOUBLE_HIT,
    NO_HIT
} hit_type_e;

class ActionManager
{
    typedef enum {
        ACTION_HIT,
        ACTION_GND,
        NO_ACTION,
    } action_type_e;

    private:
        unsigned long _time_last_hit;
        action_type_e _player_actions[2];

    public:
        ActionManager();
        void reset();
        void hit(player_index_e index);
        void ground(player_index_e index);
        bool isResetTime() const;
        hit_type_e getHitStatus() const;
};

#endif /* ACTIONMANAGER_HPP */
