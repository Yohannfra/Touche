#ifndef CLIENT_H
#define CLIENT_H

// Gpios
#define LED_GPIO (17)
#define LED_GPIO_BM (1ULL << LED_GPIO)

#define BUTTON_GPIO (32)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

#define GROUND_GPIO (23)
#define GROUND_GPIO_BM (1ULL << GROUND_GPIO)

// Fencing constants
#define GROUND_VALUE_CAPSENS_EPEE (40)

// prototypes
void print_chip_infos(void);
void init_esp_now();

#endif // CLIENT_H
