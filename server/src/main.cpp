#include <WiFi.h>
#include <esp_now.h>
#include <Arduino.h>
#include "server.hpp"
#include "LedRing.hpp"
#include "constants.hpp"

message_t message;
time_t time_last_hit = 0;
bool player_hit[2] = {false, false};
unsigned long player_ground_touched[2] = {0, 0};
LedRing led_ring_p1(LED_TOUCH_1);
LedRing led_ring_p2(LED_TOUCH_2);

void blink_both(int pin1, int pin2)
{
    led_ring_p1.setAllColors(RED);
    led_ring_p2.setAllColors(GREEN);
    delay(1000);
    led_ring_p1.turnOff();
    led_ring_p2.turnOff();
}

void play_buzzer(bool state)
{
    #if 0
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
    led_ring_p1.setAllColors(ORANGE);
    led_ring_p2.setAllColors(ORANGE);
    delay(500);
    led_ring_p1.turnOff();
    led_ring_p2.turnOff();
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    switch (message.payload) {
        case HIT:
            hit(message.index_sender);
            break;
        case GROUND:
            ground_touched(message.index_sender);
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
            if (player_hit[0])
                led_ring_p1.setAllColors(RED);
            if (player_hit[1])
                led_ring_p2.setAllColors(GREEN);
            play_buzzer(true);
            delay(FENCING_BLINKING_TIME);
            led_ring_p1.turnOff();
            led_ring_p2.turnOff();
            play_buzzer(false);
            player_hit[0] = false;
            player_hit[1] = false;
            time_last_hit = 0;
        } else {
            if (player_hit[0])
                led_ring_p1.setAllColors(RED);
            if (player_hit[1])
                led_ring_p2.setAllColors(GREEN);
            if (player_hit[0] || player_hit[1])
                play_buzzer(true);
        }
    }
}
