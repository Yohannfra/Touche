#ifndef CAPTOUCH_H
#define CAPTOUCH_H

// --------------------------------- Prototypes -------------------------------- //
/*
* @brief Get captouch value
* @param gpio gpio to read captouch from
*/
int get_captouch(int gpio);

/*
* @brief initialize captouch
* @param gpio gpio to initialize
*/
void init_captouch(int gpio);

#endif /* CAPTOUCH_H */