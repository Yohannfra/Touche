#include "actions_handler/actions_handler.h"
#include "buzzer/buzzer.h"
#include "led/led.h"
#include "led_ring/led_ring.h"
#include "protocol.h"
#include "radio/radio.h"

#include <assert.h>
#include <logging/log.h>
#include <nrf.h>
#include <stdlib.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(main_server, LOG_LEVEL_INF);

void main()
{
    LOG_INF("Starting main");

    // init led
    __ASSERT(led_init() == EXIT_SUCCESS, "Led init failed");

    // init radio
    __ASSERT(radio_init() == EXIT_SUCCESS, "Radio init failed");
    __ASSERT(radio_start_rx() == EXIT_SUCCESS, "Radio rx setup failed");

    // init buzzer
    __ASSERT(buzzer_init() == EXIT_SUCCESS, "Buzzer init failed");

    __ASSERT(led_ring_init() == 0, "Led ring init failed");

    while (1) {
        struct esb_payload *packet = radio_get_last_message();
        if (packet) {
            payload_type_e payload_type = GET_PAYLOAD(packet->data[0]);
            touche_role_e role = GET_ROLE(packet->data[0]);

            switch (payload_type) {
                case HIT:
                    LOG_INF("Received message");
                    led_set();
                    led_ring_set_color(RGB_COLOR_GREEN);
                    buzzer_start();
                    k_sleep(K_MSEC(FENCING_BLINKING_TIME));
                    buzzer_stop();
                    led_ring_turn_off();
                    break;
                default:
                    LOG_ERR("Invalid payload %d", payload_type);
                    break;
            }
        }
    }
}
