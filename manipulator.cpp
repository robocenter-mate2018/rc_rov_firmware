#include "manipulator.hpp"
#include "config.h"
rov::manipulator::manipulator():
	m_axisX(config::manipulator::AXISX_PIN1, config::manipulator::AXISX_PIN2), 
	m_axisY(config::manipulator::AXISY_PIN1, config::manipulator::AXISY_PIN2),
	m_valX(0), m_valY(0)
{
}

void rov::manipulator::init()
{
	m_axisX.init();
	m_axisY.init();
}

void rov::manipulator::run(const data_store & store)
{
	rotate(store.get_control().manipulator_rotate);
	open_close(store.get_control().manipulator_open_close);
}

void rov::manipulator::commit(data_store &store)
{
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
