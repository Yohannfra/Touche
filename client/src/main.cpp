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
    pinMode(BUTTON_PIN, INPUT);
}

unsigned short getCurrentBoardIndex()
{
    String mac_addr = WiFi.macAddress();
    Serial.println(mac_addr);
    for (int i = 0; i < 3; i++) {
        // Serial.println(MAC_ADDR_LIST_STR[SERIAL_ID - 1][i]);
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
    if (digitalRead(BUTTON_PIN)) {
        send_message();
        blink_led(LED_PIN);
    }
}
