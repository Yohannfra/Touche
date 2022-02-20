#ifndef ACTIONS_HANDLER_H
#define ACTIONS_HANDLER_H

#include "protocol.h"

typedef enum {
    NONE = 0,
    HIT_PLAYER_1,
    HIT_PLAYER_2,
    DOUBLE_HIT,
} action_type_e;

/**
 * @brief reset internals variables of the action actions handler
 */
void action_handler_reset();

/**
 * @brief Register a hit to the actions handler
 *
 * @param role the player who hit
 */
void action_handler_hit(touche_role_e role);

/**
 * @brief Check if the time elapsed since the last hit is
 * greater than the time to blink in fencing
 *
 * @return true if it is greater than the time to blink in fencing
 * @return false if it is not greater than the time to blink in fencing
 */
bool action_handler_is_reset_time();

/**
 * @brief Get the current hit status
 *
 * @return the type of the current action
 */
action_type_e action_handler_get_status();

#endif
