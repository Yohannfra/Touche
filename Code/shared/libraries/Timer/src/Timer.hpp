/*
Touché Project
Copyright (C) 2024 Assouline Yohann

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>

/**
 * @brief A basic timer class wrapping the millis() function
 */
class Timer {
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
    explicit Timer(bool startDirectly = false);

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
