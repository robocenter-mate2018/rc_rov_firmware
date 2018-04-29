#pragma once
#include "device.h"
#include "MS5837.h"
class depth_sensor : public device
{
public:
	depth_sensor();
	~depth_sensor();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void subscribe_on_serial(rc_rov *parrent);

	virtual void on_serial_event();
private:
	rovlibs::MS5837 m_sensor;
	float m_depth;
};

