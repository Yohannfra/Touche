#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/touch_pad.h"
#include "esp_log.h"

void init_captouch(void)
{
    touch_pad_init();
    // touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
}

int get_captouch(int gpio)
{
    (void)gpio;

    return 0;
}

void task_captouch(void *pvParameter)
{


}