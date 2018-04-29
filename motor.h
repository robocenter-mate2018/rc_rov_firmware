#pragma once

#include <Servo.h>

class motor
{
public:
	motor();
	void set(int pin, int mult);
	~motor();
	void init();
	void write(int8_t p);
private:
	int m_pin;
	int m_mult;
	Servo m_driver;
};

