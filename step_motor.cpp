#include "step_motor.h"
#include <Arduino.h>
//#include <SoftPWM.h>

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
	//SoftPWMBegin();
	//SoftPWMSet(m_pin_left, 0);
	//SoftPWMSet(m_pin_right, 0);
	
}


void step_motor::write(int8_t power)
{
	if (power > 0) {
		//SoftPWMSet(m_pin_left, 0);
		//SoftPWMSet(m_pin_right, 0);
	//	digitalWrite(m_pin_left, HIGH);
	//	digitalWrite(m_pin_right, LOW);
	} else if (power < 0) {
		//SoftPWMSet(m_pin_left, 0);
		//SoftPWMSet(m_pin_right, 150);
		//digitalWrite(m_pin_left, LOW);
		//digitalWrite(m_pin_right, HIGH);
	}
	else {
//		SoftPWMSet(m_pin_left, 150);
	//	SoftPWMSet(m_pin_right, 0);
		//digitalWrite(m_pin_left, LOW);
		///digitalWrite(m_pin_right, LOW);
	}
}

step_motor::~step_motor()
{
}
