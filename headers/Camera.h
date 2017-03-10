#pragma once
#include "Constants.h"

class Camera
{
public:
	Camera(float sensibility, float speed, glm::vec3 vertical, float FOV, float ratio, float near, float far);
	Camera(int left, int right, int bottom, int top);
	~Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void Move(SDL_Event &event);

	void orienter(int xRel, int yRel);
	void invert_pitch();
	void move(const glm::vec3 &position);
	glm::vec3 getPosition() { return glm::vec3(m_position.x ,- m_position.y , m_position.z); }

private:
	float sensibility;
	float speed;
	float m_phi;
	float m_theta;
	glm::vec3 m_orientation;
	glm::vec3 m_vertical;
	glm::vec3 m_lateral;
	glm::vec3 m_position;
	glm::vec3 m_aim;
	glm::mat4 m_projection;

	int x, y, x2, y2;
	int *x1;
	int *y1;




};