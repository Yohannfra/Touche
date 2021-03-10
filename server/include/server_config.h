#ifndef SERVER_PINOUT_H
#define SERVER_PINOUT_H

#define NB_NEOPIXEL_RING 2

#if NB_NEOPIXEL_RING != 2 && NB_NEOPIXEL_RING != 1
#error "NB_NEOPIXEL_RING MUST BE 1 or 2"
#endif

// The pin used for the buzzer
#define BUZZER_PIN 10

// The pin used for the led ring
#define LED_RING_PIN 3

#define NRF24L01_CE_PIN 7

#define NRF24L01_CS_PIN 8

#endif /* SERVER_PINOUT_H */