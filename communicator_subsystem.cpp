#include "communicator_subsystem.h"
#include "config.h"
#include "rov_data_types.hpp"
#include "nanopi_comunicator.h"
#include "mini_communicator.h"

communicator_subsystem::communicator_subsystem()
{
	int i = 0;
#ifdef COMMUNICATOR_NANOPI_ENABLED
	m_communicator[i++] = new nanopi_comunicator();
#endif
#ifdef COMMUNICATOR_MINI_ENABLED
	m_communicator[i++] = new mini_communicator();
#endif
}


communicator_subsystem::~communicator_subsystem()
{
}

void communicator_subsystem::init()
{
	for (int i = 0; i < COMMUNICATOR_SIZE; i++) {
		m_communicator[i]->init();
	}
}

void communicator_subsystem::run(const data_store & store)
{
	for (int i = 0; i < COMMUNICATOR_SIZE; i++) {
		m_communicator[i]->run(store);
	}
}

void communicator_subsystem::commit(data_store & store)
{
	for (int i = 0; i < COMMUNICATOR_SIZE; i++) {
		m_communicator[i]->commit(store);
	}
}

void communicator_subsystem::register_on_serial(rc_rov * parrent)
{
	for (int i = 0; i < COMMUNICATOR_SIZE; i++) {
		m_communicator[i]->subscribe_on_serial(parrent);
	}
}
