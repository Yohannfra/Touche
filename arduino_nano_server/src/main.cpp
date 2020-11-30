#include "Buzzer.hpp"
#include "LedRing.hpp"
#include "RadioModule.hpp"

#include <Arduino.h>

#include "protocol.h"
#include "fencingConstants.h"

#define BUZZER_PIN 14 // FIXME
#define LED_RING_PIN 3

Buzzer buzzer(BUZZER_PIN);
LedRing led_ring(LED_RING_PIN);
RadioModule radio_module;

device_id_t knowns_ids[2] = {0, 0};

void setup()
{
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial
    }
    radio_module.init();
    led_ring.init();
}

void register_player(int8_t id)
{
    if (knowns_ids[0] == 0) { // register player 1
        knowns_ids[0] = id;
        led_ring.blink(RED_RGB, 200);
    } else if (knowns_ids[1] == 0) { // register player 2
        knowns_ids[1] = id;
        led_ring.blink(GREEN_RGB, 200);
    } else { // UNKNOW GUY
        Serial.print("UNKNOWN ID: ");
        Serial.println(id);
    }
}

void loop()
{
    packet_t packet = radio_module.receiveMsg();

    if (packet) {
        Serial.print("Received: ");
        Serial.println(packet);

        device_id_t id = GET_ID(packet);

        if (id == knowns_ids[0]) { // player 1
            led_ring.set_color(RED_RGB);
            delay(FENCING_BLINKING_TIME);
            led_ring.turn_off();
        } else if (id == knowns_ids[1]) { // player 2
            led_ring.set_color(GREEN_RGB);
            delay(FENCING_BLINKING_TIME);
            led_ring.turn_off();
        } else { // unregistered id
            register_player(id);
        }
    }
}