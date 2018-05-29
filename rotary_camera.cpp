#include "rotary_camera.h"
#include "config.h"


rotary_camera::rotary_camera() 
{
	m_last_val[0] = 0;
	m_last_val[1] = 0;
}


rotary_camera::~rotary_camera()
{
	for (int i = 0; i < 2; i++) {
		m_cameras[i].cam.detach();
	}
}

void rotary_camera::init()
{
	m_cameras[0].cam.attach(config::cameras::front::pin);
	m_cameras[0].angle = config::cameras::front::DEFAULT_ANGLE;
	m_cameras[0].min_angle = config::cameras::front::MIN_ANGLE;
	m_cameras[0].max_angle = config::cameras::front::MAX_ANGLE;

	m_cameras[1].cam.attach(config::cameras::back::pin);
	m_cameras[1].angle = config::cameras::back::DEFAULT_ANGLE;
	m_cameras[1].min_angle = config::cameras::back::MIN_ANGLE;
	m_cameras[1].max_angle = config::cameras::back::MAX_ANGLE;

	for (int i = 0; i < CAMERAS_SIZE; i++) {
		m_cameras[i].cam.write(m_cameras[i].angle);
	}
}

void rotary_camera::run(const data_store & store)
{
	for (int i = 0; i < CAMERAS_SIZE; i++) {
		if (m_last_val[i] != store.get_control().camera_rotate[i]) {
			m_last_val[i] = store.get_control().camera_rotate[i];
			m_cameras[i].time.restart();
			rotate_cam(m_cameras[i], m_last_val[i]);
			m_cameras[i].updated = true;
		}
		if (m_cameras[i].time.elapsed() > 30 || m_cameras[i].updated) {
			rotate_cam(m_cameras[i], m_last_val[i]);
			m_cameras[i].updated = false;
			m_cameras[i].time.restart();
		}
	}
	
}

void rotary_camera::commit(data_store & store)
{
	for (int i = 0; i < 2; i++) {
		store.get_telimetry().camera_rotate[i] = m_cameras[i].angle;
	}
}

void rotary_camera::rotate_cam(rot_cam & cam_, int8_t val) {
	cam_.angle += constrain(val, -2, 2);
	cam_.angle = constrain(cam_.angle, cam_.min_angle, cam_.max_angle);
	cam_.cam.write(cam_.angle);
}
