/*
 Name:		rc_rov_firmware.ino
 Created:	01.04.2018 16:59:03
 Author:	zinjk
*/

// the setup function runs once when you press reset or power the board
#include "rov_data_types.hpp"
#include "motor.h"
#include "manipulator.hpp"
rov_types::rov_hardware_control hc;

motor v[4];
motor h[4];
rov::manipulator man;

void setup() {
	Serial.begin(115200);

	h[0].set(2); h[0].init();
	h[1].set(2); h[1].init();
	h[2].set(2); h[2].init();
	h[3].set(2); h[3].init();
	
	v[0].set(2); v[0].init();
	v[1].set(2); v[1].init();
	v[2].set(2); v[2].init();
	v[3].set(2); v[3].init();

	man.init();
	//Serial.println("inited");
}

bool updated = false;
// the loop function runs over and over again until power down or reset
void loop() {

	if (updated) {
		for (int i = 0; i < 4; i++) {
			v[i].write(hc.vertical_power[i]);
			v[i].write(hc.horizontal_power[i]);
		}
		man.write(hc);
		updated = false;
	}
	
}

void serialEvent() {
	uint8_t packet[255];
	size_t i = 0;
	delay(1);
	while (Serial.available()) {
		packet[i++] = Serial.read();
	}
	auto e = hc.deserialize(packet, i);
	//Serial.println(i);
	Serial.write(rov_types::serializable::error_to_string(e).c_str());
	updated = true;
}