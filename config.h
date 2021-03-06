#pragma once

namespace config {

/*
SERIAL SUBSCRIBER IDX CONFIG
*/
	struct serial_subcriber {
		enum : uint8_t {
			serial = 0,
			serial1 = 1,
			serial2 = 2,
			serial3 = 3
		};
	};

/*
	SUBSYSTEMS CONFIG
*/

#define SUBSYSTEM_PAYLOAD_ENABLED
#define SUBSYSTEM_THRUSTER_ENABLED
#define SUBSYSTEM_SENSORS_ENABLED
#define SUBSYSTEM_COMMUNICATOR_ENABLED

#define SUBSYSTEM_SIZE 4

/*
COMMUNICATOR CONFIG
*/

#define COMMUNICATOR_NANOPI_ENABLED
#define COMMUNICATOR_MINI_ENABLED
#define COMMUNICATOR_ESP
#define COMMUNICATOR_SIZE (3)

#define nanopi Serial
#define nanopi_serial_number (0)
#define nanopi_boudrate (115200)

#define mini_payload Serial1
#define mini_serial_number (1)
#define mini_boudrate (115200)

#define esp Serial2
#define esp_serial_number (2)
#define esp_boudrate (115200)

struct communicator_baudrate {
	enum : uint32_t {
		SERIAL_BAUDRATE = 115200,
		SERIAL1_BAUDRATE = 115200,
		SERIAL2_BAUDRATE = 115200,
		SERIAL3_BAUDRATE = 115200
	};
};
struct serial_buffer {
	enum : uint8_t {
		size = 100,
	};
};

/*
THRUSTERS CONFIG
*/
#define THRUSTER_SIZE (8)

struct thrusters {
	struct horizontal {
		struct pins {
			enum : int {
				FRONT_LEFT_PIN = 6,
				FRONT_RIGHT_PIN = 2,
				BACK_LEFT_PIN = 9,
				BACK_RIGHT_PIN = 7
			};
		};
	};
	struct veritacal {
		struct pins {
			enum : int {
				FRONT_LEFT_PIN = 5,
				FRONT_RIGHT_PIN = 3,
				BACK_LEFT_PIN = 8,
				BACK_RIGHT_PIN = 4				
			};
		};
	};
};


/*
	PAYLOAD CONFIG
*/
#define PAYLOAD_MANIPULATOR_ENABLED 
#define PAYLOAD_ROTARYCAMERA_ENABLED 

#define PAYLOAD_SIZE 2


	struct manipulator {
		enum : uint8_t {
			AXISX_PIN1 = 24,
			AXISX_PIN2 = 25,
			AXISY_PIN1 = 23,
			AXISY_PIN2 = 26
		};
	};

#define CAMERAS_SIZE (2)

	struct cameras {
		struct front {
			enum : uint8_t {
				pin = 28,
			};
			static constexpr int  DEFAULT_ANGLE = 90;
			static constexpr int  MIN_ANGLE = 0;
			static constexpr int  MAX_ANGLE = 180;
		};
		struct back {
			enum : uint8_t {
				pin = 29,
			};
			static constexpr int  DEFAULT_ANGLE = 90;
			static constexpr int  MIN_ANGLE = 0;
			static constexpr int  MAX_ANGLE = 180;
		};
	};


/*
SENSOR CONFIG
*/

#define SENSOR_DEPTH_ENABLED 


#define SENSOR_SIZE 1




}
