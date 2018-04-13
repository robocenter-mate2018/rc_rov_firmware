#pragma once
#include "data_store.h"

class subsystem;
class rc_rov;

class device
{
public:
	device();
	~device();

	virtual void init() = 0;
	virtual void run(const data_store &store) = 0;
	virtual void commit(data_store &store) = 0;

	virtual void subscribe_on_serial(rc_rov *parrent);

	virtual void on_serial_event();
private:

};

