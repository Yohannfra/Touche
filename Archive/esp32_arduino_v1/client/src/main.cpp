#include <esp_now.h>
#include <WiFi.h>
#include "constants.hpp"
#include "client.hpp"
#include "my_espNow.hpp"
#include "Utils.hpp"
#include <Arduino.h>

message_t message;

void setupPins()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
}

unsigned short getCurrentBoardIndex()
{
    String mac_addr = WiFi.macAddress();

    printDebugLog(mac_addr.c_str());
    printDebugLog("\n");
    for (int i = 0; i < 3; i++) {
        if (mac_addr == MAC_ADDR_LIST_STR[SERIAL_ID - 1][i])
            return i;
    }
    printDebugLog("Mac address not found in MAC_ADDR_LIST\n");
    handleError(); // Should go to sleep here TODO
    return 0; // NEVER READ
}

void setupDefaultMessage()
{
    message.index_sender = getCurrentBoardIndex();
    message.payload = HIT;
}

void setup()
{
    setupSerial(115200);

    if (setupEspNow() != ESP_OK) {
        printDebugLog("Error initializing ESP-NOW\n");
        handleError();
    }
    setupDefaultMessage();
    setupPins();
}

void loop()
{
    int res = analogRead(BUTTON_PIN); // change to digitalRead

    if (res > 3000) { // Change that for digitalRead !
        message.payload = HIT;
        if (sendMessage(&message) == ESP_OK) {
            delay(FENCING_BLINKING_TIME);
        }
        blinkLed(LED_PIN);
    }

    int res_ground = touchRead(GROUND_PIN);

    Serial.println(res_ground);
    if (res_ground < GROUND_VALUE_CAPSENS_EPEE) {
        message.payload = GROUND;
        message.capsensValue = res_ground;
        sendMessage(&message);
        Serial.println(res_ground);
        delay(500);
    }
}
