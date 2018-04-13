#pragma once
#include "subsystem.h"
#include "config.h"

class communicator_subsystem : public subsystem
{
public:
	communicator_subsystem();
	~communicator_subsystem();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void register_on_serial(rc_rov *parrent);
private:
	device *m_communicator[COMMUNICATOR_SIZE];
};

