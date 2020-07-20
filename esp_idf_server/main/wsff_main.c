#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_timer.h"

#include "driver/gpio.h"
#include "esp_now.h"
#include "esp_log.h"

#include "server.h"
#include "constants.h"

time_t time_last_hit = 0;
payload_types_e player_hit[2] = {NONE, NONE};
static unsigned int time_ground_touched_discrete_color = 0;

void restart_board(void)
{
    printf("Restarting...\n");
    fflush(stdout);
    esp_restart();
}

void init_gpios(void)
{
    gpio_config_t io_conf;

    // LED RING 1
    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interupt
    io_conf.mode = GPIO_MODE_OUTPUT; // output gpio
    io_conf.pin_bit_mask = LED_RING_1_GPIO; // the pin bitmask
    io_conf.pull_down_en = 0; //disable pull-down mode
    io_conf.pull_up_en = 0; //disable pull-up mode
    gpio_config(&io_conf);

    // LED RING 2
    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interupt
    io_conf.mode = GPIO_MODE_OUTPUT; // output gpio
    io_conf.pin_bit_mask = LED_RING_2_GPIO; // the pin bitmask
    io_conf.pull_down_en = 0; //disable pull-down mode
    io_conf.pull_up_en = 0; //disable pull-up mode
    gpio_config(&io_conf);

    // BUTTON GPIO
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BUTTON_GPIO_BM;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);

    // BUZZER GPIO
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = BUZZER_GPIO;
    io_conf.pull_down_en = 1;
    gpio_config(&io_conf);
}

void reset_values()
{

}


void playBuzzer(bool state)
{
    if (state)
        return;
}

void app_main()
{
    print_chip_infos();
    init_gpios();
    init_esp_now();
    esp_timer_init();

    ESP_LOGI("Server", "Init Done. Starting the main loop");

    while (true) {
        if (time_last_hit) {
            if (player_hit[PLAYER_1] == HIT) {
                /* ledRingP1.setAllColors(RED); */
            } else if (player_hit[PLAYER_1] == GROUND) {
                /* ledRingP1.setDiscretColor(ORANGE); */
                time_ground_touched_discrete_color = esp_timer_get_time();
            }
            if (player_hit[PLAYER_2] == HIT) {
                /* ledRingP2.setAllColors(GREEN); */
            } else if (player_hit[PLAYER_2] == GROUND) {
                /* ledRingP2.setDiscretColor(ORANGE); */
                time_ground_touched_discrete_color = esp_timer_get_time();
            }
            playBuzzer(player_hit[PLAYER_1] == HIT || player_hit[PLAYER_2] == HIT);
            if (time_last_hit - esp_timer_get_time() > FENCING_BLINKING_TIME ||
                time_ground_touched_discrete_color - esp_timer_get_time() > FENCING_LAPS_GROUND_NO_TOUCH) {
                reset_values(); // Time's up, we reset everything
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
