#include "sensor_subsystem.h"

#include "depth_sensor.h"

sensor_subsystem::sensor_subsystem()
{
	int i = 0;
#ifdef SENSOR_DEPTH_ENABLED
	m_sensors[i++] = new depth_sensor();
#endif // !MANIPULATOR_ENABLED
}


sensor_subsystem::~sensor_subsystem()
{
	for (int i = 0; i < SENSOR_SIZE; i++) {
		delete m_sensors[i];
	}
}

void sensor_subsystem::init()
{
	for (int i = 0; i < SENSOR_SIZE; i++) {
		m_sensors[i]->init();
	}
}

void sensor_subsystem::run(const data_store & store)
{
	for (int i = 0; i < SENSOR_SIZE; i++) {
		m_sensors[i]->run(store);
	}
}

void sensor_subsystem::commit(data_store & store)
{
	for (int i = 0; i < SENSOR_SIZE; i++) {
		m_sensors[i]->commit(store);
	}
}

void sensor_subsystem::register_on_serial(rc_rov * parrent)
{
	for (int i = 0; i < SENSOR_SIZE; i++) {
		m_sensors[i]->subscribe_on_serial(parrent);
	}
}
