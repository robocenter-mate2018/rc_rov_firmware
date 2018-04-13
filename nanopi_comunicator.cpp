#include "nanopi_comunicator.h"
#include "config.h"
#include "serializable.hpp"
#include "rc_rov.h"


nanopi_comunicator::nanopi_comunicator() : m_updated(false)
{
}

nanopi_comunicator::~nanopi_comunicator()
{
}

void nanopi_comunicator::init()
{
	nanopi.begin(config::communicator_baudrate::SERIAL_BAUDRATE);
}

void nanopi_comunicator::run(const data_store & store)
{
	//TODO: make send to nanopi hardware telimetry
}

void nanopi_comunicator::commit(data_store &store)
{
	if (m_updated) {
		store.set_control(m_last_control);
		m_updated = false;
	}
}

void nanopi_comunicator::subscribe_on_serial(rc_rov * parrent)
{
	parrent->register_serial(config::serial_subcriber::serial, this);
}

void nanopi_comunicator::on_serial_event()
{
	uint8_t packet[config::serial_buffer::size];
	rov_types::rov_hardware_control hc;
	size_t i = 0;
	delay(1);
	while (nanopi.available()) {
		packet[i++] = nanopi.read();
	}
	auto e = hc.deserialize(packet, i);
	if (rov_types::serializable::check_for_success(e)) {
		m_last_control = hc;
		m_updated = true;
	}
}
