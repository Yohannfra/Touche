#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>

#define LED_RING_1_GPIO (12)
#define LED_RING_1_GPIO_BM (1ULL << LED_RING_1_GPIO)

#define LED_RING_2_GPIO (26)
#define LED_RING_2_GPIO_BM (1ULL << LED_RING_2_GPIO)

#define BUZZER_GPIO (17)
#define BUZZER_GPIO_BM (1ULL << BUZZER_GPIO)

#define BUTTON_GPIO (14)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

// buzzer.cpp
void playBuzzer(bool state);

void print_chip_infos(void);
void init_esp_now();

#endif // SERVER_H
