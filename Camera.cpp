#include "Camera.h"


using namespace glm;


const double toRadian(float angle) {

	return angle *  M_PI / 180;
}

Camera::Camera(int left, int right, int bottom, int top) {
	m_projection = ortho(left, right, bottom, top);
	m_phi = 0.F;
	m_theta = 0.F;
	m_orientation = vec3(5, 0, 0);
	m_lateral = vec3(0);
	m_position = vec3(0, 3, 0);
	m_aim = vec3(0, 0, 0);
	x = 0;
	y = x;
}



Camera::Camera(float sensibility, float speed, glm::vec3 vertical, float FOV, float ratio, float near, float far) :sensibility(sensibility), speed(speed), m_vertical(vertical)
{
	m_projection = perspective(FOV, ratio, near, far);
	m_phi = 0.F;
	m_theta = 0.F;
	m_orientation = vec3(5, 0, 0);
	m_vertical = vertical; 
	m_lateral = vec3(0);
	m_position = vec3(0, 3, 0);
	m_aim = vec3(0, 0, 0);
	x = 0;
	y = x;
}


Camera::~Camera()
{
}


void Camera::orienter(int xRel, int yRel) {

	m_phi += -yRel * sensibility;
	m_theta += -xRel * sensibility;


	m_phi = clamp(m_phi, -89.F, 89.F);




	double p_radian = toRadian(m_phi);
	double t_radian = toRadian(m_theta);

	if (m_vertical.z == 1) {
		m_orientation = vec3(
			cos(p_radian)*cos(t_radian),
			cos(p_radian)*sin(t_radian),
			sin(p_radian));
	}
	else if (m_vertical.y == 1) {
		m_orientation = vec3(
			cos(p_radian)*sin(t_radian),
			sin(p_radian),
			cos(t_radian)*cos(p_radian));
	}
	else if (m_vertical.x == 1) {
		m_orientation = vec3(
			sin(p_radian),
			cos(p_radian)*cos(t_radian),
			sin(t_radian)*cos(p_radian));

	}

	m_lateral = cross(m_vertical, m_orientation);
	m_lateral = normalize(m_lateral);
	m_aim = m_position + m_orientation;



}



void  Camera::Move(SDL_Event &event) {

	x1 = &x2;
	y1 = &y2;


	if (event.type == SDL_MOUSEMOTION) {
		SDL_GetMouseState(x1, y1);


		orienter(x-x2, y - y2);

	}

	if (event.type == SDL_KEYDOWN) {

		if (event.key.keysym.sym == SDLK_z) {
			m_position = m_position + m_orientation * +speed;
			m_aim = m_position + m_orientation;

		}
		if (event.key.keysym.sym == SDLK_s) {
			m_position = m_position - m_orientation * +speed;
			m_aim = m_position + m_orientation;

		}
		if (event.key.keysym.sym == SDLK_d) {
			m_position = m_position + m_lateral * +speed;
			m_aim = m_position + m_orientation;

		}
		if (event.key.keysym.sym == SDLK_q) {
			m_position = m_position - m_lateral*+speed;
			m_aim = m_position + m_orientation;

		}


	}





	SDL_GetMouseState(x1, y1);

	x = x2;
	y = y2;




}


mat4 Camera::getViewMatrix() {




	return  lookAt(m_position, m_aim, m_vertical);
}

mat4 Camera::getProjectionMatrix() {


	return m_projection;
}


void Camera::move(const vec3 &pos) {
	m_position = pos;
}


void Camera::invert_pitch() {

	m_aim.y = -m_aim.y;
}