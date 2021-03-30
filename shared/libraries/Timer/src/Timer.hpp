#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>

/**
 * @brief A basic timer class wrapping the millis() function
 */
class Timer
{
    private:
        /**
         * @brief internal time representation
         */
        unsigned long _time;

    public:
        /**
         * @brief Construct a new Timer object
         *
         * @param startDirectly if true starts the timer
         */
        Timer(bool startDirectly = false);

        /**
         * @brief start the timer
         */
        void start();

        /**
         * @brief reset the timer to 0
         */
        void reset();

        /**
         * @brief get time elapsed since the timer started (in ms)
         *
         * @return the time elapsed since the timer started (in ms)
         */
        unsigned long getTimeElapsed();

        /**
         * @brief get if the timer is running
         *
         * @return true if running, false otherwise
         */
        bool isRunning();
};

#endif /* TIMER_HPP */
