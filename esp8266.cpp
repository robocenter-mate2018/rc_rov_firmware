#include "esp8266.h"

#include "config.h"

esp8266::esp8266() : m_timeout(0), m_response_recvieved(true), m_state(0)
{
}


esp8266::~esp8266()
{
}

void esp8266::init()
{
	esp.begin(esp_boudrate);
}

void esp8266::run(const data_store & store)
{
	request(m_commands[m_state]);
	should_step();
}

void esp8266::commit(data_store & store)
{
	if (m_obs_data_updated) {
		//save to store
		m_obs_data_updated = false;
	}
}

void esp8266::subscribe_on_serial(rc_rov * parrent)
{
	parrent->register_serial(esp_serial_number, this);
}

void esp8266::on_serial_event()
{
	while (esp.available()) {
		m_last_response += esp.readString();
	}

	m_response_recvieved = replay_check(m_last_response, m_state);
	should_step();
}

void esp8266::send_request(String request)
{
	request += "\r\n";
	esp.write(request.c_str());
	m_last_response = "";
	m_response_recvieved = false;
	m_timer.restart();
	m_timeout = 10000;
}

void esp8266::next(bool flag)
{
	if (flag) {
		m_state = m_state_mach[m_state][0];
	}
	else {
		m_state = m_state_mach[m_state][1];
	}
}

void esp8266::should_step()
{
	if (m_response_recvieved) {
		if (m_state == 4) {
			m_obs_data = m_last_response;
			m_obs_data_updated = true;
		}
		next(true);
	}
	if (m_timer.elapsed() > m_timeout) {

		next(false);
	}
}

bool esp8266::replay_check(const String & str, int idx)
{
	for (int i = 0; i < 3; i++) {
		if (str.indexOf(state_rep[idx][i]) == -1) {
			return false;
		}
	}
	return true;
}

void esp8266::request(const String & cmd)
{
	if (m_response_recvieved) {
		send_request(cmd);
	}
}
