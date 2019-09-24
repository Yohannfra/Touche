#include "led_matrix.h"

#define PIN_CLK 25
#define PIN_CS 26
#define PIN_DIN 27

LedMatrix ledmatrix(PIN_CLK, PIN_CS, PIN_DIN);

void setup()
{
	ledmatrix.init();
}

void loop()
{
	ledmatrix.turn_light_on_arrow_style(1);
	delay(1500);
	ledmatrix.turn_light_on_arrow_style(2);
	delay(1500);
}
