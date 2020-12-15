#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "client.h"
#include <stdint.h>
#include "esp_log.h"
#include "esp_timer.h"

#include "esp_sleep.h"
#include "esp_wifi.h"

extern int64_t time_since_last_action;

static void go_to_deep_sleep()
{
    esp_wifi_stop();
    gpio_set_level(LED_GPIO, true);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    gpio_set_level(LED_GPIO, false);

    ESP_LOGI("Client", "Going to sleep, bye bye");
    esp_deep_sleep_start();
}

void sleep_handle_task(void *pvParameter)
{
    while(1) {
        if (esp_timer_get_time() - time_since_last_action >
                                                    TIME_NO_ACTION_BEFORE_SLEEP) {
            go_to_deep_sleep();
        }
        vTaskDelay(10000 / portTICK_PERIOD_MS); // 10 secs
    }
}
