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
    uint8_t mac_tmp[6];
    int values[6];

    sscanf(WiFi.macAddress().c_str(), "%x:%x:%x:%x:%x:%x%*c",
    &values[0], &values[1], &values[2], &values[3], &values[4], &values[5]);

    for(int i = 0; i < 6; ++i )
       mac_tmp[i] = (uint8_t)values[i];

    // for (int i = 0; i < 3; i++) {
    //     if ()
    // }
    return 1;
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
