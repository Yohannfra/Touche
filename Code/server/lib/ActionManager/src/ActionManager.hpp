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

#ifndef ACTIONMANAGER_HPP
#define ACTIONMANAGER_HPP

#include <stdint.h>
#include "protocol.h"

/**
 * @brief All possible type of hits
 *
 */
typedef enum : uint8_t {
    HIT_PLAYER_1 = 0,
    HIT_PLAYER_2 = 1,
    DOUBLE_HIT = 2,
    NO_HIT = 3
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
        typedef enum : uint8_t {
            ACTION_HIT = 0,
            NO_ACTION = 1,
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
        void hit(wsff_role_e role);

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
