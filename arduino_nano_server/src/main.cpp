#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"

#include <Arduino.h>

#define BUZZER_PIN 14
#define LED_RING_1_PIN 7
#define LED_RING_2_PIN 4

Buzzer buzzer(14);
LedRing led_ring_1(LED_RING_1_PIN);
LedRing led_ring_2(LED_RING_2_PIN);
RadioModule radio_module();

void setup()
{
    Serial.begin(9600);

    led_ring_1.init();
}

void loop()
{
    led_ring_1.set_color(RED_RGB);
    delay(1000);
    led_ring_1.set_color(GREEN_RGB);
    delay(1000);
    led_ring_1.turn_off();
    delay(1000);
}