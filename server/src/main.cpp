#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "server.hpp"
#include "LedRing.hpp"
#include "constants.hpp"
#include "Utils.hpp"

message_t message;
time_t time_last_hit = 0;
bool player_hit[2] = {false, false};
unsigned long player_ground_touched[2] = {0, 0};
LedRing ledRingP1(LED_TOUCH_1);
LedRing ledRingP2(LED_TOUCH_2);

void blinkBoth(int pin1, int pin2)
{
    ledRingP1.setAllColors(RED);
    ledRingP2.setAllColors(GREEN);
    delay(1000);
    ledRingP1.turnOff();
    ledRingP2.turnOff();
}

void playBuzzer(bool state)
{
#ifndef DEBUG
    digitalWrite(BUZZER_PIN, state);
#endif
}

void hit(int player_id)
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

void ground_touched(int player_id)
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

void setup_pins()
{
    pinMode(BUZZER_PIN, OUTPUT);
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
    esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
    if (time_last_hit != 0) {
        if (millis() - time_last_hit > FENCING_LAPS_DOUBLE_TOUCH) {
            if (player_hit[0])
                ledRingP1.setAllColors(RED);
            if (player_hit[1])
                ledRingP2.setAllColors(GREEN);
            playBuzzer(true);
            delay(FENCING_BLINKING_TIME);
            ledRingP1.turnOff();
            ledRingP2.turnOff();
            playBuzzer(false);
            player_hit[0] = false;
            player_hit[1] = false;
            time_last_hit = 0;
        } else {
            if (player_hit[0])
                ledRingP1.setAllColors(RED);
            if (player_hit[1])
                ledRingP2.setAllColors(GREEN);
            if (player_hit[0] || player_hit[1])
                playBuzzer(true);
        }
    }
}
