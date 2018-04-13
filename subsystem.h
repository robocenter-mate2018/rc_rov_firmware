#pragma once
#include "data_store.h"
#include "device.h"
#include "rc_rov.h"
class subsystem
{
public:
	subsystem();
	~subsystem();
	
	virtual void init() = 0;
	virtual void run(const data_store &store) = 0;
	virtual void commit(data_store &store) = 0;

	virtual void register_on_serial(rc_rov *parrent);
};

