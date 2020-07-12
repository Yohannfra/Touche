#ifndef CLIENT_H
#define CLIENT_H

#define LED_GPIO (12)
#define BUTTON_GPIO (14)
#define GROUND_GPIO (23)

#define LED_GPIO_BM (1ULL << LED_GPIO)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)
#define GROUND_GPIO_BM (1ULL << GROUND_GPIO)

void print_chip_infos(void);
void init_esp_now();

#endif // CLIENT_H
