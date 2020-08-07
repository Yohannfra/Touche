#ifndef LEDRING_H
#define LEDRING_H

#define LED_COUNT (12)

#define GREEN_RGB 0, 0xff, 0
#define RED_RGB 0xff, 0, 0
#define ORANGE_RGB 0xff, 0x7f, 0
#define BLACK_RGB 0, 0, 0

void setAllColors(const char rgb[3]);
void setDiscretColor(const char rgb[3]);
void turnOff();

#endif // LEDRING_H
