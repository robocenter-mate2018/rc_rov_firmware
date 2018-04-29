#include "rc_rov.h"
#include "device.h"
#include "subsystem.h"
#include "payload_subsystem.h"
#include "communicator_subsystem.h"
#include "thruster_subsystem.h"
#include "sensor_subsystem.h"



rc_rov::rc_rov()
{
	int i = 0;
#ifdef SUBSYSTEM_COMMUNICATOR_ENABLED 
	m_subsystems[i++] = new communicator_subsystem();
#endif
#ifdef SUBSYSTEM_PAYLOAD_ENABLED 
	m_subsystems[i++] = new payload_subsystem();
#endif
#ifdef SUBSYSTEM_THRUSTER_ENABLED 
	m_subsystems[i++] = new thruster_subsystem();
#endif
#ifdef SUBSYSTEM_SENSORS_ENABLED 
	m_subsystems[i++] = new sensor_subsystem();
#endif
}

rc_rov::~rc_rov()
{
	for (int i = 0; i < SUBSYSTEM_SIZE; i++) {
		delete m_subsystems[i];
	}
}

void rc_rov::init()
{
	for (int i = 0; i < SUBSYSTEM_SIZE; i++) {
		m_subsystems[i]->init();
		m_subsystems[i]->register_on_serial(this);
	}
	
}

void rc_rov::loop()
{
	for (int i = 0; i < SUBSYSTEM_SIZE; i++) {
		m_subsystems[i]->run(m_data_store);
		m_subsystems[i]->commit(m_data_store);
	}
	m_led.loop();
}

void rc_rov::interrupt_serial(uint8_t idx)
{
	if (m_subscriber_event != NULL) {
		m_subscriber_event[idx]->on_serial_event();
	}
	
}
void rc_rov::register_serial(uint8_t idx, device * subscriber)
{
	if (subscriber != NULL) {
		m_subscriber_event[idx] = subscriber;
	}
}
