#if 0
#include "led_matrix.h"

#define PIN_CLK 25
#define PIN_CS 26
#define PIN_DIN 27

LedMatrix ledmatrix(PIN_CLK, PIN_CS, PIN_DIN);

void setup()
{
    ledmatrix.init();
}

void loop()
{
    ledmatrix.turn_light_on_arrow_style(1);
    ledmatrix.turn_light_on(1);
    delay(1500);
    ledmatrix.turn_light_on_arrow_style(2);
    delay(1500);
}

#include <WiFi.h>
#include "led_matrix.h"

#define PIN_CLK 25
#define PIN_CS 26
#define PIN_DIN 27

const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";
WiFiServer server(80);


LedMatrix ledmatrix(PIN_CLK, PIN_CS, PIN_DIN);

void setup()
{
    Serial.begin(115200);
    Serial.print("Setting AP (Access Point)…");
    WiFi.softAP(ssid);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    server.begin();
    ledmatrix.init();
    ledmatrix.turn_light_off();
}

void loop()
{
    WiFiClient client = server.available();   // Listen for incoming clients

    if (client) {                             // If a new client connects,
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            ledmatrix.turn_light_on(1);
            delay(1);
        }
        ledmatrix.turn_light_off();
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }


    WiFiClient client = server.available();   // listen for incoming clients

    if (client) {
        Serial.println("New Client.");           // print a message out the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            ledmatrix.turn_light_on(1);
        }
        client.stop();
        ledmatrix.turn_light_off();
        Serial.println("Client Disconnected.");
    }
}

#endif
