#include "actions_handler.h"

#include <zephyr.h>

static int64_t time_last_hit = 0;
static bool player_hits[2] = {false, false};

void action_handler_reset()
{
    time_last_hit = 0;
    player_hits[PLAYER_1] = false;
    player_hits[PLAYER_2] = false;
}

void action_handler_hit(touche_role_e role)
{
    if (time_last_hit == 0) { // first hit
        time_last_hit = k_uptime_get();
        player_hits[role] = true;
    } else { // maybe double hit
        if (k_uptime_delta(&time_last_hit) <= FENCING_LAPS_DOUBLE_HIT) {
            player_hits[role] = true;
        }
    }
}

bool action_handler_is_reset_time()
{
    return time_last_hit > 0 && k_uptime_delta(&time_last_hit) > FENCING_BLINKING_TIME;
}

action_type_e action_handler_get_status()
{
    if (player_hits[PLAYER_1] && player_hits[PLAYER_2]) {
        return DOUBLE_HIT;
    } else if (player_hits[PLAYER_1]) {
        return HIT_PLAYER_1;
    } else if (player_hits[PLAYER_2]) {
        return HIT_PLAYER_2;
    }
    return NONE;
}
