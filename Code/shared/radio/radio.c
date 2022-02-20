#include "radio.h"

#include <drivers/clock_control.h>
#include <drivers/clock_control/nrf_clock_control.h>
#include <logging/log.h>
#include <stdlib.h>
#include "../led/led.h"

LOG_MODULE_REGISTER(radio, LOG_LEVEL_INF);

static struct esb_payload rx_payload = {0};
static bool has_new_payload = false;

static int clocks_start(void)
{
    int err;
    int res;
    struct onoff_manager *clk_mgr;
    struct onoff_client clk_cli;

    clk_mgr = z_nrf_clock_control_get_onoff(CLOCK_CONTROL_NRF_SUBSYS_HF);
    if (!clk_mgr) {
        LOG_ERR("Unable to get the Clock manager");
        return -ENXIO;
    }

    sys_notify_init_spinwait(&clk_cli.notify);

    err = onoff_request(clk_mgr, &clk_cli);
    if (err < 0) {
        LOG_ERR("Clock request failed: %d", err);
        return err;
    }

    do {
        err = sys_notify_fetch_result(&clk_cli.notify, &res);
        if (!err && res) {
            LOG_ERR("Clock could not be started: %d", res);
            return res;
        }
    } while (err);

    LOG_DBG("HF clock started");
    return EXIT_SUCCESS;
}

static void event_handler(struct esb_evt const *event)
{
    switch (event->evt_id) {
        case ESB_EVENT_TX_SUCCESS:
            LOG_DBG("TX SUCCESS EVENT");
            break;
        case ESB_EVENT_TX_FAILED:
            LOG_DBG("TX FAILED EVENT");
            break;
        case ESB_EVENT_RX_RECEIVED:
            if (esb_read_rx_payload(&rx_payload) == 0) {
                LOG_INF("Packed received!");
                has_new_payload = true;
            } else {
                LOG_ERR("Error while reading rx packet");
            }
            break;
    }
}

struct esb_payload *radio_get_last_message()
{
    if (!has_new_payload) {
        return NULL;
    }
    has_new_payload = false;
    return &rx_payload;
}

int radio_init()
{
    struct esb_config config = ESB_DEFAULT_CONFIG;

    /* These are arbitrary default addresses. In end user products
     * different addresses should be used for each set of devices.
     */
    uint8_t base_addr_0[4] = {0xE7, 0xE7, 0xE7, 0xE7};
    uint8_t base_addr_1[4] = {0xC2, 0xC2, 0xC2, 0xC2};
    uint8_t addr_prefix[8] = {0xE7, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8};

    config.protocol = ESB_PROTOCOL_ESB;
    config.payload_length = 1;
    config.retransmit_delay = 600;
    config.bitrate = ESB_BITRATE_1MBPS;
    config.event_handler = event_handler;
    config.mode = ESB_MODE_PTX;
    config.tx_mode = ESB_TXMODE_AUTO;
    config.selective_auto_ack = false;

    if (esb_init(&config)) {
        LOG_ERR("Error: esb_init");
        return EXIT_FAILURE;
    }

    if (clocks_start()) {
        LOG_ERR("Error: clocks_start");
        return EXIT_FAILURE;
    }

    if (esb_set_base_address_0(base_addr_0)) {
        LOG_ERR("Error: esb_set_base_address_0");
        return EXIT_FAILURE;
    }

    if (esb_set_base_address_1(base_addr_1)) {
        LOG_ERR("Error: esb_set_base_address_1");
        return EXIT_FAILURE;
    }

    if (esb_set_prefixes(addr_prefix, ARRAY_SIZE(addr_prefix))) {
        LOG_ERR("Error: esb_set_prefixes");
        return EXIT_FAILURE;
    }
    LOG_INF("ESB INIT OK");
    return EXIT_SUCCESS;
}

int radio_send_msg(uint8_t data)
{
    LOG_INF("Sending msg");

    struct esb_payload tx_payload = {
        .pipe = 0,
        .length = 1 * sizeof(uint8_t),
        .data =
            {
                data,
            },
    };

    int err = esb_write_payload(&tx_payload);
    if (err) {
        LOG_ERR("Write payload, err %d", err);
        return EXIT_FAILURE;
    }
    LOG_INF("Write OK!");

    return EXIT_SUCCESS;
}

int radio_disable()
{
    esb_disable();
    return EXIT_SUCCESS;
}

int radio_start_rx()
{
    int err = esb_start_rx();
    if (err) {
        LOG_ERR("RX setup failed, err %d", err);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int radio_start_tx()
{
    int err = esb_start_tx();
    if (err) {
        LOG_ERR("TX setup failed, err %d", err);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
