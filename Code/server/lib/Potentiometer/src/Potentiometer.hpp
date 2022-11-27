/*
Touché Project
Copyright (C) 2021 Assouline Yohann

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

#ifndef POTENTIOMETER_HPP
#define POTENTIOMETER_HPP

#include <Arduino.h>

/**
 * @brief Abstract potentiometer usage
 *
 */
class Potentiometer {
  public:
    /**
     * @brief Construct a new Potentiometer object
     *
     * @param pin arduino pin for the potentiometer value reading
     */
    explicit Potentiometer(byte pin);

    /**
     * @brief Get the mapped value from 0 to 200
     *
     * @return int the mapped value
     */
    int getMappedValue();

    /**
     * @brief Get the raw value of analogRead
     *
     * @return int the raw value
     */
    int getRawValue();

  private:
    /**
    * @brief Pin attached to the potentiometer
    */
    byte _pin;
};

#endif  // POTENTIOMETER_HPP
