#include "rotary_camera.h"
#include "config.h"


rotary_camera::rotary_camera()
{
}


rotary_camera::~rotary_camera()
{
}

void rotary_camera::init()
{
	m_cameras[0].cam.attach(config::cameras::front::pin);
	m_cameras[0].angle = config::cameras::front::DEFAULT_ANGLE;
	m_cameras[0].min_angle = config::cameras::front::MIN_ANGLE;
	m_cameras[0].min_angle = config::cameras::front::MAX_ANGLE;

	m_cameras[1].cam.attach(config::cameras::back::pin);
	m_cameras[1].angle = config::cameras::back::DEFAULT_ANGLE;
	m_cameras[1].min_angle = config::cameras::back::MIN_ANGLE;
	m_cameras[1].min_angle = config::cameras::back::MAX_ANGLE;
	for (int i = 0; i < CAMERAS_SIZE; i++) {
		m_cameras[i].cam.write(m_cameras[i].angle);
	}
}

void rotary_camera::run(const data_store & store)
{
	for (int i = 0; i < CAMERAS_SIZE; i++) {
		/*rotate_cam(m_cameras[i], store.get_telimetry().rr)
		m_cameras[i].cam.write(m_cameras[i].angle);*/
	}
}

void rotary_camera::commit(data_store & store)
{
}

void rotary_camera::rotate_cam(rot_cam & cam_, int8_t val) {
	cam_.angle += constrain(val, -2, 2);
	cam_.angle = constrain(cam_.angle, cam_.min_angle, cam_.max_angle);
	cam_.cam.write(cam_.angle);
}