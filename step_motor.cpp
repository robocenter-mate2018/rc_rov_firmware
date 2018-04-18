#include "step_motor.h"
#include <Arduino.h>

//#define PWMCONTROL

#ifdef PWMCONTROL
#include <SoftPWM.h>
#endif
step_motor::step_motor()
{
}

step_motor::step_motor(int8_t pin_l, int8_t pin_r) : m_pin_left(pin_l), m_pin_right(pin_r)
{
}

void step_motor::set(int8_t pin_l, int8_t pin_r)
{
	m_pin_left = pin_l;
	m_pin_right = pin_r;
}

void step_motor::init()
{
#ifdef PWMCONTROL
	SoftPWMBegin();
	SoftPWMSet(m_pin_left, 0);
	SoftPWMSet(m_pin_right, 0);
#else
	pinMode(m_pin_left, OUTPUT);
	pinMode(m_pin_right, OUTPUT);
#endif
}


void step_motor::write(int8_t power)
{
	if (power > 0) {
#ifdef PWMCONTROL
		SoftPWMSet(m_pin_left, 0);
		SoftPWMSet(m_pin_right, 0);
#else
		digitalWrite(m_pin_left, HIGH);
		digitalWrite(m_pin_right, LOW);
#endif
	} else if (power < 0) {
#ifdef PWMCONTROL
		SoftPWMSet(m_pin_left, 0);
		SoftPWMSet(m_pin_right, 150);
#else
		digitalWrite(m_pin_left, LOW);
		digitalWrite(m_pin_right, HIGH);
#endif
	}
	else {
#ifdef PWMCONTROL
		SoftPWMSet(m_pin_left, 150);
		SoftPWMSet(m_pin_right, 0);
#else
		digitalWrite(m_pin_left, LOW);
		digitalWrite(m_pin_right, LOW);
#endif
	}
}

step_motor::~step_motor()
{
}
