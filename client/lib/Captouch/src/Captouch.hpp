/**
 * @file Captouch.hpp
 * @brief captouch class header
 * @author Assouline Yohann
 * @date 2020-12-24
 */

#ifndef CAPTOUCH_HPP
#define CAPTOUCH_HPP

#include <CapacitiveSensor.h>

/**
 * @brief A wrapper arround CapacitiveSensor lib
 */
class Captouch
{
    private:
        /**
         * @brief
         */
        uint8_t pin_out;

        /**
         * @brief
         */
        CapacitiveSensor capacitive_sensor;

        /**
         * @brief
         */
        uint8_t pin_in;

        /**
         * @brief
         */
        long _calibrationSum;

        /**
         * @brief
         */
        long _calibrationIndex;

        /**
         * @brief
         */
        long _threshold;

    public:
        /**
         * @brief default constructor
         *
         * @param pin_out
         * @param pin_in
         */
        Captouch(uint8_t pin_out, uint8_t pin_in);

        /**
         * @brief
         *
         * @return
         */
        bool trigger_ground();

        /**
         * @brief
         *
         * @return
         */
        long get_value();

        /**
         * @brief
         *
         * @return
         */
        bool calibrate();

        /**
         * @brief
         *
         * @param success
         */
        void end_calibration(bool success);
};

#endif /* CAPTOUCH_HPP */
