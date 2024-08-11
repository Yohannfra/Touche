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

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>

/**
 * @brief Class to abstract a button (INPUT_PULLUP only)
 */
class Button {
  public:
    /**
    * @brief Construct a new Button object
    *
    * @param pin arduino pin used for the button
    */
    explicit Button(uint8_t pin);

    /**
    * @brief Check if the button is pressed
    *
    * @return true the button is pressed
    * @return false the button is not pressed
    */
    bool isPressed();

  private:
    /**
    * @brief arduino pin used for the button
    */
    uint8_t _pin;
};

#endif  // BUTTON_HPP
