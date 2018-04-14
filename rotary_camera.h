#pragma once
#include "device.h"
#include <Servo.h>
#include "config.h"

class rotary_camera : public device
{
public:
	rotary_camera();
	~rotary_camera();

	virtual void init();
	virtual void run(const data_store &store);
	virtual void commit(data_store &store);
private:
	
	struct rot_cam {
		Servo cam;
		int angle = 0;
		int max_angle = 0;
		int min_angle = 0;
	};
	
	rot_cam m_cameras[CAMERAS_SIZE];
	int8_t m_last_val[2];
	void rotate_cam(rot_cam &cam_, int8_t val);
	
};

