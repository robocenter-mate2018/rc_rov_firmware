#include "thruster_subsystem.h"


thruster_subsystem::thruster_subsystem()
{
	int i = 0;

	m_motors[i++].set(config::thrusters::horizontal::pins::FRONT_LEFT_PIN, -1);
	m_motors[i++].set(config::thrusters::horizontal::pins::FRONT_RIGHT_PIN, 1);
	m_motors[i++].set(config::thrusters::horizontal::pins::BACK_LEFT_PIN, -1);
	m_motors[i++].set(config::thrusters::horizontal::pins::BACK_RIGHT_PIN, 1);

	m_motors[i++].set(config::thrusters::veritacal::pins::FRONT_LEFT_PIN, 1);
	m_motors[i++].set(config::thrusters::veritacal::pins::FRONT_RIGHT_PIN, -1);
	m_motors[i++].set(config::thrusters::veritacal::pins::BACK_LEFT_PIN, -1);
	m_motors[i++].set(config::thrusters::veritacal::pins::BACK_RIGHT_PIN, 1);	
}


thruster_subsystem::~thruster_subsystem()
{

}

void thruster_subsystem::init()
{
	for (int i = 0; i < THRUSTER_SIZE; i++) {
		m_motors[i].init();
	}

}

void thruster_subsystem::run(const data_store & store)
{
	for (int i = 0; i < 4; i++) {
		m_motors[i].write(store.get_control().horizontal_power[i]);
	}

	for (int i = 0; i < 4; i++) {
		m_motors[i + 4].write(store.get_control().vertical_power[i]);
	}
}

void thruster_subsystem::commit(data_store & store)
{
}
