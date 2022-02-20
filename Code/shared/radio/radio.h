#ifndef RADIO_H
#define RADIO_H

#include <esb.h>
#include <stdbool.h>
#include <stdint.h>

int radio_init();

int radio_send_msg(uint8_t data);

int radio_disable();

int radio_start_rx();

int radio_start_tx();

struct esb_payload *radio_get_last_message();

#endif
