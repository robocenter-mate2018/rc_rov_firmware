#pragma once
#include "subsystem.h"
#include "motor.h"
class thruster_subsystem : public subsystem
{
public:
	thruster_subsystem();
	~thruster_subsystem();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

private:
	motor m_motors[THRUSTER_SIZE];
};

