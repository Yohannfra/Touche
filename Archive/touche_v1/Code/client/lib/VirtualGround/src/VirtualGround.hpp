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

#ifndef CAPTOUCH_HPP
#define CAPTOUCH_HPP

#include <CapacitiveSensor.h>

/**
 * @brief A wrapper arround CapacitiveSensor lib
 */
class VirtualGround {
  private:
    /**
    * @brief output pin for capacitive sensor
    */
    uint8_t _pin_out;

    /**
    * @brief input pin for capacitive sensor
    */
    uint8_t _pin_in;

    /**
    * @brief capasitiveSensor instance
    */
    CapacitiveSensor _capacitive_sensor;

    /**
    * @brief variable used during calibration, it's the sum of the values and at the end of calibration
    * we have _treshold = _calibrationSum / _calibrationIndex
    */
    long _calibrationSum;

    /**
    * @brief variable used during calibration, it's the number of values read
    */
    long _calibrationIndex;

    /**
    * @brief capasitive threshold, it's set during calibration.
    * when a hit occure, we compare this value with the value of get_value()
    * and it determines if the hit occure on the guard.
    */
    long _threshold;

    /**
    * @brief Tolerance that is applied to check if guard is hit is set to 10% of the _treshold
    */
    long _tolerance;

    /**
    * @brief Enable/disable metalic piste detection
    */
    bool _pisteEnabled;

  public:
    /**
    * @brief default constructor
    *
    * @param pin_out output pin for capacitive sensor
    * @param pin_in input pin for capacitive sensor
    */
    VirtualGround(uint8_t pin_out, uint8_t pin_in);

    /**
    * @brief check if the get_value() value is close to _treshold
    * Use this function during a hit to check if it's on the guard
    *
    * @return True if yes, False otherwise.
    */
    bool trigger_ground();

    /**
    * @brief get CapacitiveSensor raw value
    *
    * @return the raw value
    */
    long get_value();

    /**
    * @brief calibrate the CapacitiveSensor, this function needs to be called in a loop until it returns true.
    *
    * @return true if the calibration is over, false otherwise
    */
    bool calibrate();

    /**
    * @brief end the calibration process, set the treshold value (only if sucess == true)
    * and reset all variables used during calibration for a futur use
    *
    * @param success if the calibration process was a sucess.
    */
    void end_calibration(bool success);

    /**
    * @brief Enable/disable piste mode
    *
    * @param state state of the piste mode
    */
    void setPisteEnabled(bool state);

    /**
    * @brief reset all past calibration, values etc. Call it when the weapon changes
    *
    */
    void reset();
};

#endif /* CAPTOUCH_HPP */
