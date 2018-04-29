#include "motor.h"
#include <Arduino.h>


motor::motor(): m_pin(0)
{
 
}

void motor::set(int pin, int mult)
{
	m_pin = pin;
	m_mult = mult;
}



motor::~motor()
{
	m_driver.detach();
}

void motor::init()
{
	m_driver.attach(m_pin);
	write(0);
}

void motor::write(int8_t p)
{
	uint16_t pulse = 1500 + (m_mult * p * 5);
	pulse = constrain(pulse, 1000, 2000);
	m_driver.writeMicroseconds(pulse);

}
