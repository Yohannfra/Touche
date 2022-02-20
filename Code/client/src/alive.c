#include <zephyr.h>
#include "led.h"

static void alive_led_blinker_worker(struct k_work *work)
{
    led_set();
    k_sleep(K_MSEC(250));
    led_clear();
}

K_WORK_DEFINE(alive_led_blinker, alive_led_blinker_worker);

static void alive_timer_timeout_handler(struct k_timer *timer_id)
{
    k_work_submit(&alive_led_blinker);
}

K_TIMER_DEFINE(alive_timer, alive_timer_timeout_handler, NULL);

void alive_timer_start(void)
{
    k_timer_start(&alive_timer, K_SECONDS(0), K_SECONDS(5));
}

void alive_timer_reset(void)
{
    k_timer_start(&alive_timer, K_SECONDS(5), K_SECONDS(5));
}
