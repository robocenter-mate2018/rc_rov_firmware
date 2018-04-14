#include "nanopi_comunicator.h"
#include "config.h"
#include "serializable.hpp"
#include "rc_rov.h"
#include "timer.h"

nanopi_comunicator::nanopi_comunicator() : m_updated(false)
{
}

nanopi_comunicator::~nanopi_comunicator()
{
}

void nanopi_comunicator::init()
{
	nanopi.begin(115200);
}

void nanopi_comunicator::run(const data_store & store)
{
	if (m_timer.elapsed() > 25) {
		m_timer.stop();
		uint8_t buffer[100];
		rov_types::rov_hardware_telimetry t = store.get_telimetry();
		uint8_t size = t.serialize(buffer);
		nanopi.write(buffer, size);
	}

	if (!m_timer.is_started()) {
		m_timer.start();
	}
}

void nanopi_comunicator::commit(data_store &store)
{
	store.get_telimetry().mega_communication = 1;
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
