#pragma once
#include <stdint.h>

class step_motor
{
public:
	step_motor();
	step_motor(int8_t pin_l, int8_t pin_r);
	void set(int8_t pin_l, int8_t pin_r);
	void init();
	void write(int8_t power);
	~step_motor();
private:
	int8_t m_pin_left;
	int8_t m_pin_right;
};

