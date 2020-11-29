#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"

#include <Arduino.h>

#define BUZZER_PIN 14 // FIXME
#define LED_RING_PIN 3

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module;

void setup()
{
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial
    }
    radio_module.init();
    led_ring.init();
}

void loop()
{
    long tmp;
    if ((tmp = radio_module.receiveMsg())) {
        Serial.print("Received: ");
        Serial.println(tmp);
        led_ring.set_color(RED_RGB);
        delay(500);
        led_ring.turn_off();
        delay(500);
    }
    // led_ring.set_color(RED_RGB);
    // delay(500);
    // led_ring.set_half_colors(RED_RGB, GREEN_RGB);
    // delay(500);
    // led_ring.turn_off();
    // delay(500);
}