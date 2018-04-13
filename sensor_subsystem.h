#pragma once
#include "subsystem.h"
#include "device.h"
class sensor_subsystem : public subsystem
{
public:
	sensor_subsystem();
	~sensor_subsystem();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void register_on_serial(rc_rov *parrent);
private:
	device *m_sensors[SENSOR_SIZE];
};

