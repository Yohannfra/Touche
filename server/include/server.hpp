#ifndef SERVER_HPP
#define SERVER_HPP

#include "constants.hpp"

#define LED_TOUCH_1 (12)
#define LED_TOUCH_2 (26)
#define LED_RING (12)
#define BUZZER_PIN (17)

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif // SERVER_HPP
