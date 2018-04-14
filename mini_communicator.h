#pragma once
#include "data_store.h"
#include "rc_rov.h"
class mini_communicator : public device
{
public:
	mini_communicator();
	~mini_communicator();
	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void subscribe_on_serial(rc_rov *parrent);

	virtual void on_serial_event();
private:
	rov_types::rov_mini_control m_last_control;
	rov_types::rov_mini_telimetry m_last_telimetry;
	bool m_updated;
};

