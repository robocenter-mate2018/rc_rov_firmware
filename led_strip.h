#pragma once
#include "timer.h"
#define USE_HSV
#include <WS2812.h>
#define LEDCount 8
#define outputPin 12
class led_strip
{
public:
	led_strip();
	~led_strip();
	void loop();

private:
	int cut(int idx);
	WS2812 m_led;
	int m_led_idx;
	timer m_timer;

	int h = 0;   //stores 0 to 614
	byte steps = 15; //number of hues we skip in a 360 range per update

	byte sat = 255;
	byte val = 127;
	cRGB value;
	cRGB valueblack;

	void set_black();
	void draw();

	void Cycle()
	{
		value.SetHSV(h, sat, val);
		valueblack.SetHSV(0, 0, 0);

		h += steps;
		if (h > 360)
		{
			h %= 360;
		}
	}
};

