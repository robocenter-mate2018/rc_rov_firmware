#pragma once
#include "subsystem.h"
#include "config.h"
class payload_subsystem : public subsystem
{
public:
	payload_subsystem();
	~payload_subsystem();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void register_on_serial(rc_rov *parrent);
private:
	device *m_payload_tools[PAYLOAD_SIZE];
};

