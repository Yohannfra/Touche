#include "button/button.h"
#include "led/led.h"
#include "protocol.h"
#include "mac_address/mac_address.h"
#include "radio/radio.h"

#include <assert.h>
#include <logging/log.h>
#include <stdlib.h>
#include <zephyr.h>

LOG_MODULE_REGISTER(main_client, LOG_LEVEL_INF);

static void print_boot_header(const uint8_t *mac_addr)
{
    LOG_INF("Starting client...");
    LOG_HEXDUMP_INF(mac_addr, 6 * sizeof(uint8_t), "Mac address");
}

void main()
{
    uint8_t mac_address[6];
    mac_address_get(mac_address);

    print_boot_header(mac_address);

    // init led
    __ASSERT(led_init() == EXIT_SUCCESS, "Led init failed");

    // init button
    __ASSERT(button_init() == EXIT_SUCCESS, "Button init failed");

    // init radio
    __ASSERT(radio_init() == EXIT_SUCCESS, "Radio init failed");

    // blink led after init
    led_blink(1000, 1);

    while (true) {
        if (button_get_state()) {
            LOG_INF("Sending HIT");
            led_set();
            radio_send_msg(HIT);
            k_sleep(K_MSEC(FENCING_BLINKING_TIME));
            led_clear();
        }
    }
}
