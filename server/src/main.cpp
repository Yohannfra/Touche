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

void blink_both(int pin1, int pin2)
{
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    delay(1000);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&message, incomingData, sizeof(message_t));
    if (message.payload == HIT) {
        if (message.index_sender == CLIENT_1_MAC_ADDR_INDEX * SERIAL_ID) {
            blink_led(LED_TOUCH_1);
        } else if (message.index_sender == CLIENT_2_MAC_ADDR_INDEX * SERIAL_ID){
            blink_led(LED_TOUCH_2);
        } else {
            blink_both(LED_TOUCH_1, LED_TOUCH_2);
        }
    }
}

void setup_pins()
{
    pinMode(LED_TOUCH_1, OUTPUT);
    pinMode(LED_TOUCH_2, OUTPUT);
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
}
