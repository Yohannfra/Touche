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

#include "VirtualGround.hpp"

#include "ArduinoLog.h"

#include <CapacitiveSensor.h>

static const int MAX_CALIBRATIONS_SAMPLES = 100;

VirtualGround::VirtualGround(uint8_t pin_out, uint8_t pin_in) :
    _pin_out(pin_out), _pin_in(pin_in), _capacitive_sensor(_pin_out, _pin_in)
{
    _capacitive_sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);  // turn off autocalibrate
    _capacitive_sensor.set_CS_Timeout_Millis(2500);
    _calibrationSum = 0;
    _calibrationIndex = 0;
    _threshold = 0;
    _tolerance = 0;
    _pisteEnabled = false;
}

long VirtualGround::get_value()
{
    // 5 is a good compromise to have both speed and precision
    return _capacitive_sensor.capacitiveSensorRaw(5);
}

bool VirtualGround::trigger_ground()
{
    if (_threshold == 0) {
        return false;
    }

    const uint8_t NB_OF_TIME_TO_SAMPLE = 5;
    long sum = 0;

    for (uint8_t i = 0; i < NB_OF_TIME_TO_SAMPLE; i++) {
        long val = this->get_value();
        Log.trace("trigger_ground value: %l", val);
        sum += val;
    }
    sum = sum / NB_OF_TIME_TO_SAMPLE;

    Log.trace("trigger_ground final: %l", sum);

    // I still need to test it with a real metal piste so it might be wrong
    if (_pisteEnabled && sum > _threshold) {
        return true;
    }

    if (_threshold - _tolerance <= sum && sum <= _threshold + _tolerance) {
        return true;
    }
    return false;
}

bool VirtualGround::calibrate()
{
    long val = this->get_value();
    Log.trace("calibration val: %l", val);

    if (val >= 0) {
        _calibrationSum += val;
        _calibrationIndex += 1;
    } else {
        Log.warning("Invalid value :%l ,skipping it", val);
    }

    return _calibrationIndex == MAX_CALIBRATIONS_SAMPLES;
}

void VirtualGround::end_calibration(bool success)
{
    if (success && _calibrationIndex > 0 /* to avoid div by 0 */) {
        _threshold = _calibrationSum / _calibrationIndex;
        _tolerance = (float)_threshold / 6.66f;  //  ~ 15% of the _treshold
        Log.notice("Treshold is now: %l", _threshold);
        Log.notice("Tolerance is now: %l", _tolerance);
    }
    _calibrationIndex = 0;
    _calibrationSum = 0;
}

void VirtualGround::setPisteEnabled(bool state)
{
    _pisteEnabled = state;
}

void VirtualGround::reset()
{
    _calibrationSum = 0;
    _calibrationIndex = 0;
    _threshold = 0;
    _tolerance = 0;
}