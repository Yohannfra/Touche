#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include "server.hpp"
#include "LedRing.hpp"
#include "constants.hpp"
#include "Utils.hpp"

extern message_t message;
extern time_t time_last_hit;
extern bool player_hit[2];
extern unsigned long player_ground_touched[2];
extern LedRing ledRingP1;
extern LedRing ledRingP2;

static void hit(int player_id)
{
    if (time_last_hit == 0) {
        time_last_hit = millis();
        player_hit[player_id - 1] = true;
    } else {
        if (millis() - time_last_hit <= FENCING_LAPS_DOUBLE_TOUCH) {
            player_hit[player_id - 1] = true;
        }
    }
}

static void ground_touched(int player_id)
{
    player_ground_touched[player_id - 1] = millis();
    ledRingP1.setAllColors(ORANGE);
    ledRingP2.setAllColors(ORANGE);
    delay(500);
    ledRingP1.turnOff();
    ledRingP2.turnOff();
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    printDebugLog("Message received: ");
    printDebugLog(message.payload == HIT ? "HIT\n" : "GROUND\n");

    switch (message.payload) {
        case HIT:
            hit(message.index_sender);
            break;
        case GROUND:
            ground_touched(message.index_sender);
            printDebugLog("Capsens value: ");
            printDebugLog(message.capsensValue);
            printDebugLog("\n");
            break;
        default:
            break;
    }
}