#include "manipulator.hpp"

rov::manipulator::manipulator():
	m_axisX(24,23), m_axisY(43,34), m_valX(0), m_valY(0)
{
}

void rov::manipulator::init()
{
	m_axisX.init();
	m_axisY.init();
}

void rov::manipulator::write(const rov_types::rov_hardware_control & control)
{
	rotate(control.manipulator_rotate);
	rotate(control.manipulator_open_close);
}

rov::manipulator::~manipulator()
{
}

void rov::manipulator::rotate(int8_t power)
{
	m_valX = power;
	m_axisX.write(power);
}

void rov::manipulator::open_close(int8_t power)
{
	m_valY = power;
	m_axisY.write(power);
}
