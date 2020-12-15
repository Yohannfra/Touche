#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

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
#include "buzzer.h"
#include "neopixel_handler.h"
#include "esp_now_server.h"

int64_t time_last_hit = 0;
payload_types_e player_hit[2] = {NONE, NONE};

unsigned long player_ground_touched[2] = {0, 0};

// led rings
neopixel_data_t np1;
neopixel_data_t np2;

void init_gpios(void)
{
    // buzzer
    init_buzzer(BUZZER_GPIO_BM);

    // led rings
    np1.gpio = LED_RING_1_GPIO;
    np1.channel = RMT_CHANNEL_2;
    init_neopixel(&np1);
    turn_off_neopixel(&np1);

    np2.gpio = LED_RING_2_GPIO;
    np2.channel = RMT_CHANNEL_3;
    init_neopixel(&np2);
    turn_off_neopixel(&np2);
    usleep(1000 * 10);
}

void reset_values(void)
{
    if (np1.is_on)
        turn_off_neopixel(&np1);
    if (np2.is_on)
        turn_off_neopixel(&np2);
    if (is_buzzer_on())
        stopBuzzer();
    time_last_hit = 0;
    player_hit[PLAYER_1] = NONE;
    player_hit[PLAYER_2] = NONE;
    player_ground_touched[PLAYER_1] = 0;
    player_ground_touched[PLAYER_2] = 0;
}

void app_main()
{
    init_gpios();
    init_esp_now();
    esp_timer_init();

    while (true) {
        uint64_t current_time = esp_timer_get_time();

        if (time_last_hit && current_time - time_last_hit > TIME_BEFORE_SHOWING_HIT) {
            if (player_hit[PLAYER_1] == HIT && !np1.is_on) { // p1 hit
                set_color_neopixel(&np1, RED);
            } else if (player_hit[PLAYER_1] == GROUND && !np1.is_on) { // p1 gnd
                set_discrete_color_neopixel(&np1, ORANGE);
            }
            if (player_hit[PLAYER_2] == HIT && !np2.is_on) { // p2 hit
                set_color_neopixel(&np2, GREEN);
            } else if (player_hit[PLAYER_2] == GROUND && !np2.is_on) { // p2 gnd
                set_discrete_color_neopixel(&np2, ORANGE);
            }
            if (player_hit[PLAYER_1] == HIT || player_hit[PLAYER_2] == HIT) { // buzzer
                playBuzzer();
            } else {
                stopBuzzer();
            }
            if (time_last_hit && current_time - time_last_hit > FENCING_BLINKING_TIME) {
                reset_values(); // Time's up, we reset everything
            }
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}
