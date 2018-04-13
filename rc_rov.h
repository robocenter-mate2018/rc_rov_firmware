#pragma once
#include "data_store.h"
#include "subsystem.h"
#include "config.h"

class device;
class rc_rov {
public:
	rc_rov();
	~rc_rov();

	void init();

	void loop();

	void interrupt_serial(uint8_t idx);
	
	void register_serial(uint8_t idx, device *subscriber);
private:
	data_store m_data_store;
	subsystem *m_subsystems[SUBSYSTEM_SIZE];

	device *m_subscriber_event[4];
};

