#pragma once

#include "device.h"
#include "timer.h"
#include "rc_rov.h"

class esp8266 : public device
{
public:
	esp8266();
	~esp8266();
	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);

	virtual void subscribe_on_serial(rc_rov *parrent);

	virtual void on_serial_event();
private:
	void send_request(String request);
	void next(bool flag);
	void should_step();
	bool replay_check(const String &str, int idx);
	void request(const String &cmd);

	String m_last_response;	
	String m_obs_data;
	timer m_timer;
	unsigned long m_timeout;	
	bool m_response_recvieved;
	bool m_obs_data_updated = false;
	uint8_t m_state = 0;



	const String m_commands[5] = {
		"AT+CWLAP=\"MATE2018\"",
		"AT+CWJAP=\"MATE2018\",\"\"",
		"AT+CIPSTART=\"TCP\",\"192.168.4.1\",80",
		"AT+CIPSEND=16",
		"GET / HTTP/1.1\r\n"
	};

	const uint8_t m_state_mach[5][2] = {
		{ 1, 0 },
		{ 2, 0 },
		{ 3, 0 },
		{ 4, 0 },
		{ 2, 0 }
	};

	const String state_rep[5][3] = {
		{ "OK", "+CWLAP:", "MATE2018" },
		{ "WIFI CONNECTED", "WIFI GOT IP", "OK" },
		{ "CONNECT", "OK", "" },
		{ "OK", ">", "" },
		{ "CLOSED", "Recv", "SEND OK" },
	};
};

