#ifndef CLIENT_H
#define CLIENT_H

// --------------------------------- Gpios ------------------------------------- //
#define LED_GPIO (17)
#define LED_GPIO_BM (1ULL << LED_GPIO)

#define BUTTON_GPIO (32)
#define BUTTON_GPIO_BM (1ULL << BUTTON_GPIO)

#define GROUND_GPIO (23)
#define GROUND_GPIO_BM (1ULL << GROUND_GPIO)

// --------------------------------- Fencing constants ------------------------- //
#define GROUND_VALUE_CAPSENS_EPEE (40)

// --------------------------------- Prototypes -------------------------------- //
/*
* @brief Print a few informations about the esp32
*/
void print_chip_infos(void);

/*
* @brief send hit message to server
*/
void send_hit(void);

/*
* @brief send ground message to server
*/
void send_ground(void);

#endif // CLIENT_H