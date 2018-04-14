/*
 Name:		rc_rov_firmware.ino
 Created:	01.04.2018 16:59:03
 Author:	zinjk
*/

#include "rc_rov.h"
#include "timer.h"
rc_rov robot;

void setup() {
	robot.init();
}

void loop() {
	//timer t;
	//t.start();
	robot.loop();
	//Serial.print("time loop ");
	//Serial.println(t.elapsed());
}

void serialEvent() {
	robot.interrupt_serial(0);
}

void serialEvent1() {
	robot.interrupt_serial(1);
}

void serialEvent2() {
	robot.interrupt_serial(2);
}

void serialEvent3() {
	robot.interrupt_serial(3);
}
