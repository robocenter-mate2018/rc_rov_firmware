#pragma once

#include <Servo.h>

class motor
{
public:
	motor();
	void set(int pin);
	~motor();
	void init();
	void write(int8_t p);
private:
	int m_pin;
	Servo m_driver;
};

