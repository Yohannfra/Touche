/*
** Assouline Yohann, 2020
** WSSF
** File description:
** main client file
*/

#include <esp_now.h>
#include <WiFi.h>
#include "constants.hpp"
#include "client.hpp"
#include "my_espNow.hpp"
#include <Arduino.h>

message_t message;

void setup_pins()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

unsigned short getCurrentBoardIndex()
{
    String mac_addr = WiFi.macAddress();
    Serial.println(mac_addr);
    for (int i = 0; i < 3; i++) {
        if (mac_addr == MAC_ADDR_LIST_STR[SERIAL_ID - 1][i])
            return i;
    }
    Serial.println("Mac address not found in MAC_ADDR_LIST");
    handle_error();
    return 0; // NEVER READ
}

void setup_default_message()
{
    message.index_sender = getCurrentBoardIndex();
    message.payload = HIT;
}

void setup()
{
    Serial.begin(115200);

    if (setup_esp_now() != ESP_OK)
        return handle_error();
    setup_default_message();
    setup_pins();
}

void loop()
{
    int res = analogRead(BUTTON_PIN);

    if (res > 3000) {
        message.payload = HIT;
        send_message(&message);
        // blink_led(LED_PIN);
    }

    int res_ground = touchRead(GROUND_PIN);

    Serial.println(res_ground);
    if (res_ground < 20) {
        // message.payload = GROUND;
        // send_message(&message);
        Serial.println(res_ground);
    }
    delay(100);
}
