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

void setup_default_message()
{
    memcpy(message.id_sender, MAC_ADDR, 6);
    message.payload = TOUCH;
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
