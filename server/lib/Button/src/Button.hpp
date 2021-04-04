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
        Button(uint8_t pin);

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

#endif // BUTTON_HPP
