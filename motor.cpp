#include "motor.h"
#include <Arduino.h>


motor::motor(): m_pin(0)
{
  m_driver.writeMicroseconds(1500);
}

void motor::set(int pin)
{
	m_pin = pin;
}



motor::~motor()
{
	m_driver.detach();
}

void motor::init()
{
	m_driver.attach(m_pin);
}

void motor::write(int8_t p)
{
	uint16_t pulse = 1500 + (p * 5);
	pulse = constrain(pulse, 1000, 2000);
	m_driver.writeMicroseconds(pulse);
}
