#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>

/**
 * @brief Abstract buzzer usage
 *
 */
class Buzzer
{
    private:
        /**
         * @brief Pin attached to the buzzer
         *
         */
        byte pin;

    public:
        /**
         * @brief Construct a new Buzzer object
         *
         * @param pin Pin attached to the buzzer
         */
        Buzzer(byte pin);

        /**
         * @brief Start buzzer
         *
         */
        void play();

        /**
         * @brief Stop buzzer
         *
         */
        void stop();
};

#endif /* BUZZER_HPP */