#ifndef LEDRING_HPP
#define LEDRING_HPP

#include <Adafruit_NeoPixel.h>

#define LED_COUNT (12)
#define LED_RING_TYPE (NEO_GRB + NEO_KHZ800)

extern const char RED[3];
extern const char GREEN[3];
extern const char ORANGE[3];

class LedRing {
    public:
        LedRing(int pin);
        ~LedRing() = default;
        void setAllColors(const char rgb[3]);
        void turnOff();

    private:
        Adafruit_NeoPixel _strip;
};

#endif // LEDRING_HPP
