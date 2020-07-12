#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "server.hpp"
#include "LedRing.hpp"
#include "constants.hpp"
#include "Utils.hpp"

time_t time_last_hit = 0;
payload_types_e player_hit[2] = {NONE, NONE};
LedRing ledRingP1(LED_TOUCH_1);
LedRing ledRingP2(LED_TOUCH_2);

static unsigned int time_ground_touched_discrete_color = 0;

void setup_pins()
{
    pinMode(BUZZER_PIN, OUTPUT);
    // Add the main button bin
}

void reset_values()
{
    ledRingP1.turnOff();
    ledRingP2.turnOff();
    playBuzzer(false);
    player_hit[PLAYER_1] = NONE;
    player_hit[PLAYER_2] = NONE;
    time_last_hit = 0;
    time_ground_touched_discrete_color = 0;
}

void setup()
{
    WiFi.mode(WIFI_STA);

#ifdef DEBUG
    setupSerial(115200);
#endif
    if (esp_now_init() != ESP_OK) {
        printDebugLog("Error initializing ESP-NOW\n");
        handleError();
        return;
    }
    setup_pins();
    reset_values();
    esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
    if (time_last_hit) {
        if (player_hit[PLAYER_1] == HIT) {
            ledRingP1.setAllColors(RED);
        } else if (player_hit[PLAYER_1] == GROUND) {
            ledRingP1.setDiscretColor(ORANGE);
            time_ground_touched_discrete_color = millis();
        }
        if (player_hit[PLAYER_2] == HIT) {
            ledRingP2.setAllColors(GREEN);
        } else if (player_hit[PLAYER_2] == GROUND) {
            ledRingP2.setDiscretColor(ORANGE);
            time_ground_touched_discrete_color = millis();
        }
        playBuzzer(player_hit[PLAYER_1] == HIT || player_hit[PLAYER_2] == HIT);
        if (time_last_hit - millis() > FENCING_BLINKING_TIME ||
            time_ground_touched_discrete_color - millis() > FENCING_LAPS_GROUND_NO_TOUCH) {
            reset_values(); // Time's up, we reset everything
        }
    }
}