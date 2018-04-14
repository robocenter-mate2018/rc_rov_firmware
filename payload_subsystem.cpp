#include "payload_subsystem.h"
#include "manipulator.hpp"
#include "rotary_camera.h"

payload_subsystem::payload_subsystem()
{
	int i = 0;
#ifdef PAYLOAD_MANIPULATOR_ENABLED
	m_payload_tools[i++] = new rov::manipulator();
#endif // !MANIPULATOR_ENABLED

#ifdef PAYLOAD_ROTARYCAMERA_ENABLED
	m_payload_tools[i++] = new rotary_camera();
#endif // !MANIPULATOR_ENABLED
#ifdef PAYLOAD_ESP8266_ENABLED
	m_payload_tools[i++] = new rov::ESP8266();
#endif // !MANIPULATOR_ENABLED
}


payload_subsystem::~payload_subsystem()
{
	for (int i = 0; i < PAYLOAD_SIZE; i++) {
		delete m_payload_tools[i];
	}
}

void payload_subsystem::init()
{
	for (int i = 0; i < PAYLOAD_SIZE; i++) {
		m_payload_tools[i]->init();
	}
}

void payload_subsystem::run(const data_store & store)
{
	for (int i = 0; i < PAYLOAD_SIZE; i++) {
		m_payload_tools[i]->run(store);
	}
}

void payload_subsystem::commit(data_store & store)
{
	for (int i = 0; i < PAYLOAD_SIZE; i++) {
		m_payload_tools[i]->commit(store);
	}
}

void payload_subsystem::register_on_serial(rc_rov *parrent)
{
	for (int i = 0; i < PAYLOAD_SIZE; i++) {
		m_payload_tools[i]->subscribe_on_serial(parrent);
	}
}
