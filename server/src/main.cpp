/*
** Assouline Yohann, 2020
** WSSF
** File description:
** server main
*/

#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "server.hpp"
#include "constants.hpp"

message_t message;
time_t time_last_hit = 0;
bool player_hit[2] = {false, false};

void blink_both(int pin1, int pin2)
{
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    delay(1000);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

void play_buzzer(bool state)
{
    digitalWrite(BUZZER_PIN, state);
    // TODO
    // Play differents tones
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

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    if (message.payload == HIT) {
        hit(message.index_sender);
    }
}

void setup_pins()
{
    pinMode(LED_TOUCH_1, OUTPUT);
    pinMode(LED_TOUCH_2, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
}

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    setup_pins();
    esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
    if (time_last_hit != 0) {
        if (millis() - time_last_hit > FENCING_LAPS_DOUBLE_TOUCH) {
            digitalWrite(LED_TOUCH_1, player_hit[0]);
            digitalWrite(LED_TOUCH_2, player_hit[1]);
            play_buzzer(true);
            delay(FENCING_BLINKING_TIME);
            digitalWrite(LED_TOUCH_1, LOW);
            digitalWrite(LED_TOUCH_2, LOW);
            play_buzzer(false);
            player_hit[0] = false;
            player_hit[1] = false;
            time_last_hit = 0;
        } else {
            digitalWrite(LED_TOUCH_1, player_hit[0]);
            digitalWrite(LED_TOUCH_2, player_hit[1]);
            if (player_hit[0] || player_hit[1])
                play_buzzer(true);
        }
    }
    delay(10);
}