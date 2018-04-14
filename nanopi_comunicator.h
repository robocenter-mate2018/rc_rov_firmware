#pragma once
#include "device.h"
#include "rov_data_types.hpp"
#include "timer.h"
class nanopi_comunicator : public device
{
public:
	nanopi_comunicator();
	~nanopi_comunicator();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void subscribe_on_serial(rc_rov *parrent);

	virtual void on_serial_event();
private:
	rov_types::rov_hardware_control m_last_control;
	rov_types::rov_hardware_telimetry m_last_telimetry;
	bool m_updated;
	timer m_timer;
};

