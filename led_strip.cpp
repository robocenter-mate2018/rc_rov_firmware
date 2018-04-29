#include "led_strip.h"



led_strip::led_strip() : m_led(8), m_led_idx(0)
{
	m_timer.start();
	m_led.setOutput(12);
}


led_strip::~led_strip()
{
}

void led_strip::loop()
{
	
	if (m_timer.elapsed() > 150) {
		Cycle();
		set_black();

		draw();

		m_led.sync();
		m_timer.restart();
	}

}

int led_strip::cut(int idx)
{
	if (idx >= 8) {
		idx = 0;
	}
	return idx;
}

void led_strip::set_black()
{
	for (int i = 0; i < 8; i++)
	{
		m_led.set_crgb_at(i, valueblack);
	}
}

void led_strip::draw()
{
	m_led.set_crgb_at(m_led_idx++, value);
	m_led_idx = cut(m_led_idx);
	m_led.set_crgb_at(m_led_idx++, value);
	m_led_idx = cut(m_led_idx);
	m_led.set_crgb_at(m_led_idx++, value);
	m_led_idx = cut(m_led_idx);
}
