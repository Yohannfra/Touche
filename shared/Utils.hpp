#ifndef UTILS_HPP
#define UTILS_HPP

void printDebugLog(const char *s);

void blinkLed(byte pin);

void handleError();

void setupSerial(unsigned int baudRate);

#endif // UTILS_HPP
