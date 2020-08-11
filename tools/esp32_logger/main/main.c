#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "constants.h"
#include "esp_now_logger.h"

void app_main()
{
    init_esp_now();

    while (1) {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}