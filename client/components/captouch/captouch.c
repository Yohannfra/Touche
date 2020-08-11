#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"
#include "esp_log.h"
#include "client.h"
#include "esp_now_client.h"

// Based on peripherals/touch_pad_read

#define TOUCH_PAD_NO_CHANGE   (-1)
#define TOUCH_THRESH_NO_USE   (0)
#define TOUCH_FILTER_MODE_EN  (1)
#define TOUCHPAD_FILTER_TOUCH_PERIOD (10)

#define TOUCH_PAD_ZERO 0

// TODO : Do a capsens value sync with touching opponent epee or something

void captouch_init(void)
{
    touch_pad_init();
    touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
    touch_pad_config(TOUCH_PAD_ZERO, TOUCH_THRESH_NO_USE);
#if TOUCH_FILTER_MODE_EN
    touch_pad_filter_start(TOUCHPAD_FILTER_TOUCH_PERIOD);
#endif
}

void captouch_read_task(void *pvParameter)
{
    uint16_t touch_value;

    while (1) {
        touch_pad_read_raw_data(TOUCH_PAD_ZERO, &touch_value);
        if (touch_value < 120) { // Find the perfect value // cf TODO
            my_espnow_send_ground(touch_value);
        }
        // ESP_LOGI("Client", "Touchpad : %d", touch_value);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}