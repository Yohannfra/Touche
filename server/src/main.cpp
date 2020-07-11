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

void reset_values()
{
    ledRingP1.turnOff();
    ledRingP2.turnOff();
    playBuzzer(false);
    player_hit[0] = false;
    player_hit[1] = false;
    time_last_hit = 0;
}

void loop()
{
    if (time_last_hit) {
        if (player_hit[0]) {
            ledRingP1.setAllColors(RED);
        }
        if (player_hit[1]) {
            ledRingP2.setAllColors(GREEN);
        }
        playBuzzer(player_hit[0] || player_hit[1]);
        if (time_last_hit - millis() > FENCING_BLINKING_TIME) {
            reset_values(); // Time's up, we reset everything
        }
    }
}