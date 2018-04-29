#include "depth_sensor.h"
#include <Arduino.h>
#include <Wire.h>


depth_sensor::depth_sensor() : m_depth(-1)
{
}


depth_sensor::~depth_sensor()
{
}

void depth_sensor::init()
{
	Wire.begin();
	m_sensor.init();
	m_sensor.setModel(rovlibs::MS5837::MS5837_30BA);
	m_sensor.setFluidDensity(997); // kg/m^3 (997 freshwater, 1029 for seawater)
}

void depth_sensor::run(const data_store & store)
{
	m_sensor.read();

	if (m_sensor.depth() < 200 && m_sensor.depth() > -10) {
		m_depth = m_sensor.depth();
	}
}

void depth_sensor::commit(data_store &store)
{
	store.get_telimetry().depth = m_depth;
}

void depth_sensor::subscribe_on_serial(rc_rov * parrent)
{
}

void depth_sensor::on_serial_event()
{
}
