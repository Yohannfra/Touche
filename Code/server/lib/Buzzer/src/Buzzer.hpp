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

#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <Arduino.h>

/**
 * @brief Abstract buzzer usage
 *
 */
class Buzzer {
  private:
    /**
    * @brief Pin attached to the buzzer
    *
    */
    byte _pin;

  public:
    /**
    * @brief Construct a new Buzzer object
    *
    * @param pin Pin attached to the buzzer
    */
    explicit Buzzer(byte pin);

    /**
    * @brief Start buzzer
    *
    * @param volume audio volume from 0 to 255
    */
    void play(uint8_t volume);

    /**
    * @brief Stop buzzer
    *
    */
    void stop();
};

#endif /* BUZZER_HPP */
