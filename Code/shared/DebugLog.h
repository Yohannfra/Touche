/*
WSFF Project
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

#ifndef DEBUGLOG_HPP
#define DEBUGLOG_HPP

#include <Arduino.h>

#ifdef DEBUG
#    define DEBUG_LOG(msg)                                                    \
        do {                                                                  \
            Serial.print(msg);                                                \
        } while (0);

#    define DEBUG_LOG_LN(msg)                                                 \
        do {                                                                  \
            Serial.println(msg);                                              \
        } while (0);

#    define DEBUG_LOG_VAL(msg, val)                                           \
        do {                                                                  \
            Serial.print(msg);                                                \
            Serial.println(val);                                              \
        } while (0);
#else
#    define DEBUG_LOG(msg)                                                    \
        do {                                                                  \
        } while (0);

#    define DEBUG_LOG_LN(msg)                                                 \
        do {                                                                  \
        } while (0);
#    define DEBUG_LOG_VAL(msg, val)                                           \
        do {                                                                  \
        } while (0);
#endif

#endif /* DEBUGLOG_HPP */