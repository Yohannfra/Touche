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