#ifndef SERVER_H
#define SERVER_H

#include <stdbool.h>

#define EXTERNAL_ESP32_LOGGER 0

#if EXTERNAL_ESP32_LOGGER
#include <stdint.h>
static const uint8_t EXTERNAL_LOGGER_MAC_ADDR[6] = {0x24, 0x62, 0xAB, 0xB0, 0x73, 0x50};
#endif

#define LED_RING_1_GPIO (12)

#define LED_RING_2_GPIO (26)

#define BUZZER_GPIO (17)
#define BUZZER_GPIO_BM (1ULL << BUZZER_GPIO)

#define BUTTON_GPIO (14)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

#endif // SERVER_H
