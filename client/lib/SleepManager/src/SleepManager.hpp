#ifndef SLEEPMANAGER_HPP
#define SLEEPMANAGER_HPP

#include <Arduino.h>

/**
 * @brief a small class to abstract the sleep/wakeup functions
 *
 */
class SleepManager {
    public:
        /**
         * @brief Put the arduino to sleep
         */
        static void sleep();
};

#endif // SLEEPMANAGER_HPP
