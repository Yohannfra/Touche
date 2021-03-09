#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <stdint.h>
#include "PlayerManager.hpp"

/**
 * @brief All possible type of hits
 *
 */
typedef enum {
    HIT_PLAYER_1,
    HIT_PLAYER_2,
    DOUBLE_HIT,
    NO_HIT
} hit_type_e;

/**
 * @brief Class to handle actions and events
 *
 */
class ActionManager
{
    public:
        /**
         * @brief hit action or no action
         *
         */
        typedef enum {
            ACTION_HIT,
            NO_ACTION,
        } action_type_e;

        /**
         * @brief Construct a new Action Manager object
         *
         */
        ActionManager();

        /**
         * @brief Reset all internal variables
         *
         */
        void reset();

        /**
         * @brief Declare a hit to the actionManager
         *
         * @param index Index of the player hitting
         */
        void hit(player_index_e index);

        /**
         * @brief Check if the time elapsed since the last hit is
         * greater than the time to blink in fencing
         *
         * @return true if it is greater than the time to blink in fencing
         * @return false if it is not greater than the time to blink in fencing
         */
        bool isResetTime() const;

        /**
         * @brief Get the current hit status
         *
         * @return hit_type_e the current hit status
         */
        hit_type_e getHitStatus() const;

    private:
        unsigned long _time_last_hit;
        action_type_e _player_actions[2];
};

#endif /* ACTIONMANAGER_HPP */
