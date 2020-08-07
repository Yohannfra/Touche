#ifndef CLIENT_H
#define CLIENT_H

#include <stdint.h>

static const uint8_t SERVER_MAC_ADDR[6] = {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50};

#define LED_GPIO (17)
#define LED_GPIO_BM (1ULL << LED_GPIO)

#define BUTTON_GPIO (32)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

#define TOUCH_PAD_GPIO (23)
#define TOUCH_PAD_GPIO_BM (1ULL << TOUCH_PAD_GPIO)

#define GROUND_VALUE_CAPSENS_EPEE (40)

#endif // CLIENT_H