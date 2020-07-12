#include "LedRing.hpp"

const char RED[3] {0xFF, 0, 0};
const char GREEN[3] {0, 0xFF, 0};
const char ORANGE[3] {0xFF, 0x7F, 0};

LedRing::LedRing(int pin) : _strip(LED_COUNT, pin, LED_RING_TYPE)
{
    _strip.begin();
    turnOff();
    _strip.show();
}

void LedRing::setAllColors(const char rgb[3])
{
    for (int i = 0; i < LED_COUNT; i++) {
        _strip.setPixelColor(i, rgb[0], rgb[1], rgb[2]);
    }
    _strip.show();
}

void LedRing::setDiscretColor(const char rgb[3])
{
    for (int i = 1; i < LED_COUNT; i += 3) {
        _strip.setPixelColor(0, rgb[0], rgb[1], rgb[2]);
    }
    _strip.show();
}

void LedRing::turnOff()
{
    for (int i = 0; i < LED_COUNT; i++) {
        _strip.setPixelColor(i, 0, 0, 0);
    }
    _strip.show();
}
