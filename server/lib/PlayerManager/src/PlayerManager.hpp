#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include "protocol.h"

#define DEFAULT_ID -1

/**
 * @brief Possible types of player
 *
 */
typedef enum {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    NOT_A_PLAYER = 2
}   player_index_e;

/**
 * @brief Class for handling players connections and actions
 *
 */
class PlayerManager
{
    private:
        /**
         * @brief to store the wsff id of the players
         *
         */
        int8_t _knowns_ids[2];

        /**
         * @brief number of player connected
         *
         */
        uint8_t _player_count;

    public:
        /**
         * @brief Construct a new Player Manager object
         *
         */
        PlayerManager();

        /**
         * @brief Get the number of player connected
         *
         * @return uint8_t number of player connected
         */
        uint8_t getPlayerCount() const;

        /**
         * @brief Get the player index from his ID
         *
         * @param id player ID
         * @return player_index_e index of the player
         */
        player_index_e getPlayerFromID(int8_t id) const;

        /**
         * @brief register player
         *
         * @param id player ID
         * @return player_index_e index assigned to the player
         */
        player_index_e registerPlayer(int8_t id);
};
#endif /* PLAYERMANAGER_HPP */