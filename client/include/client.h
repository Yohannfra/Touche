#ifndef CLIENT_H
#define CLIENT_H

#include "server_mac_addr.h"

#define LED_GPIO (22)
#define LED_GPIO_BM (1ULL << LED_GPIO)

#define BUTTON_GPIO (4)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

#define TOUCH_PAD_GPIO (32)
#define TOUCH_PAD_GPIO_BM (1ULL << TOUCH_PAD_GPIO)

#define GROUND_VALUE_CAPSENS_EPEE (40)

#define TIME_NO_ACTION_BEFORE_SLEEP (150000000) // 2.5 mins

#endif // CLIENT_H
