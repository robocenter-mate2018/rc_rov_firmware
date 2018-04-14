#include "mini_communicator.h"
#include "config.h"
#include "rc_rov.h"

mini_communicator::mini_communicator()
{
	
}


mini_communicator::~mini_communicator()
{
}

void mini_communicator::init()
{
	mini_payload.begin(115200);
}

void mini_communicator::run(const data_store & store)
{
	uint8_t buffer[50];
	rov_types::rov_hardware_control control = store.get_control();
	rov_types::rov_mini_control t;
	t.acoustics = control.acoustic;
	for (int i = 0; i < 4; i++) {
		t.twisting_motors[i] = control.twisting_motors[i];
	}
	t.magnet = control.magnet;
	uint8_t size = t.serialize(buffer);
	mini_payload.write(buffer, size);
}

void mini_communicator::commit(data_store & store)
{
	store.get_telimetry().acoustic = this->m_last_telimetry.acoustics;
	store.get_telimetry().magnet = this->m_last_telimetry.magnet;
	for (int i = 0; i < 4; i++) {
		store.get_telimetry().twisting_motors[i] = this->m_last_telimetry.magnet;
	}
}

void mini_communicator::subscribe_on_serial(rc_rov * parrent)
{
	parrent->register_serial(config::serial_subcriber::serial2, this);
}

void mini_communicator::on_serial_event()
{
	uint8_t packet[config::serial_buffer::size];
	rov_types::rov_mini_telimetry hc;
	size_t i = 0;
	delay(1);
	while (mini_payload.available()) {
		packet[i++] = mini_payload.read();
	}
	auto e = hc.deserialize(packet, i);
	if (rov_types::serializable::check_for_success(e)) {
		m_last_telimetry = hc;
		m_updated = true;
	}
}
