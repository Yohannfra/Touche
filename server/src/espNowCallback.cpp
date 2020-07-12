#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "server.hpp"
#include "LedRing.hpp"
#include "constants.hpp"
#include "Utils.hpp"

static message_t message;
static unsigned long player_ground_touched[2] = {0, 0};

extern time_t time_last_hit;
extern bool player_hit[2];
extern LedRing ledRingP1;
extern LedRing ledRingP2;

#define GET_OPPONENT(id) (id == PLAYER_1) ? PLAYER_1 : PLAYER_2

static void hit(int player_id)
{
    // If a player touched but the the opponent's ground got triggered before
    if (player_ground_touched[GET_OPPONENT(player_hit)] - millis() < FENCING_LAPS_GROUND_NO_TOUCH) {
        player_hit[player_id] = GROUND;
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
        return;
    } else { // should not happend but error handling
        player_ground_touched[GET_OPPONENT(player_hit)] = 0;
    }

    if (time_last_hit == 0) {
        time_last_hit = millis();
        player_hit[player_id] = HIT;
    } else {
        if (millis() - time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            player_hit[player_id] = HIT;
        }
    }
}

static void ground_touched(int player_id)
{
    if (player_ground_touched[player_id] == 0)
        player_ground_touched[player_id] = millis();
#ifdef DEBUG
    ledRingP1.setAllColors(ORANGE);
    ledRingP2.setAllColors(ORANGE);
    delay(500);
    ledRingP1.turnOff();
    ledRingP2.turnOff();
#endif
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    printDebugLog("Message received: ");
    printDebugLog(message.payload == HIT ? "HIT\n" : "GROUND\n");

    switch (message.payload) {
        case HIT:
            hit(message.index_sender - 1);
            break;
        case GROUND:
            ground_touched(message.index_sender - 1);
            printDebugLog("Capsens value: ");
            printDebugLog(message.capsensValue);
            printDebugLog("\n");
            break;
        case NONE: // Should not happend
            break;
        case ERROR:
            break; // TODO : error handling or stuff
    }
}