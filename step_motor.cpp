#include "step_motor.h"
#include <Arduino.h>

//#define SOFTPWMCONTROL
//#define HARDPWMCONTROL
#define DIGITALCONTROL

#ifdef SOFTPWMCONTROL
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
#ifdef SOFTPWMCONTROL
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
#ifdef SOFTPWMCONTROL
		SoftPWMSet(m_pin_left, 0);
		SoftPWMSet(m_pin_right, 0);
#endif
#ifdef DIGITALCONTROL
		digitalWrite(m_pin_left, HIGH);
		digitalWrite(m_pin_right, LOW);
#endif
#ifdef HARDPWMCONTROL
		uint8_t p = (255.0f / 100.0f) * power;
		analogWrite(m_pin_left, p);
		analogWrite(m_pin_right, 0);
#endif
	} else if (power < 0) {
#ifdef SOFTPWMCONTROL
		SoftPWMSet(m_pin_left, 0);
		SoftPWMSet(m_pin_right, 150);
#endif
#ifdef DIGITALCONTROL
		digitalWrite(m_pin_left, LOW);
		digitalWrite(m_pin_right, HIGH);
#endif
#ifdef HARDPWMCONTROL
		uint8_t p = (255.0f / 100.0f) * power;
		analogWrite(m_pin_left, 0);
		analogWrite(m_pin_right, p);
#endif
	}
	else {
#ifdef SOFTPWMCONTROL
		SoftPWMSet(m_pin_left, 150);
		SoftPWMSet(m_pin_right, 0);
#endif
#ifdef DIGITALCONTROL
		digitalWrite(m_pin_left, LOW);
		digitalWrite(m_pin_right, LOW);
#endif
#ifdef HARDPWMCONTROL
		analogWrite(m_pin_left, 0);
		analogWrite(m_pin_right, 0);
#endif
	}
}

step_motor::~step_motor()
{
}
