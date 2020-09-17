#include <Arduino.h>

#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"

#define BUZZER_PIN 14
#define LED_RING_1_PIN 3
#define LED_RING_2_PIN 4

Buzzer buzzer(14);
LedRing led_ring_1(LED_RING_1_PIN);
LedRing led_ring_2(LED_RING_2_PIN);
RadioModule radio_module();

void setup()
{

}

void loop()
{

}