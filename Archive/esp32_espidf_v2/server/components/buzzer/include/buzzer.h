#ifndef BUZZER_H
#define BUZZER_H


void init_buzzer(int pin);
void playBuzzer(void);
void stopBuzzer(void);
bool is_buzzer_on(void);

#endif /* BUZZER_H */