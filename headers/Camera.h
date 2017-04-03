#pragma once
#include "Constants.h"

class ViewCamera{
public:
	ViewCamera(float FOV, float ratio, float zNear, float zFar, glm::vec3 vertical);
	ViewCamera(float left, float width, float right, float height, float zNear, float zFar, glm::vec3 vertical);
	void setPosition(glm::vec3& position); 
	void setPosition(glm::vec3& position, glm::vec3& aim); 
	glm::vec3 getPosition() { return glm::vec3(m_position.x , m_position.y , m_position.z); }
	bool isPerspectiveProjection(){ return isPerspective; }
	float getZNear(){ return zNear;  }
	void print_data(); 
	void setAim(glm::vec3 &aim){ m_aim = aim; }
	float getZFar(){ return zFar; }
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	void invert_pitch();
protected:
	float zNear;
	float zFar; 
	glm::vec3 m_aim;
	glm::mat4 m_projection;
	glm::vec3 m_position;	
	glm::vec3 m_vertical;
	bool isPerspective; 
};


class Camera : public ViewCamera
{
public:
	Camera(float sensibility, float speed, glm::vec3 vertical, float FOV, float ratio, float near, float far);
	Camera(float left, float right, float bottom, float top, float zNear, float zFar);
	~Camera();



	void Move(SDL_Event &event);

	void orienter(int xRel, int yRel);



private:
	float sensibility;
	float speed;
	float m_phi;
	float m_theta;
	glm::vec3 m_orientation;

	glm::vec3 m_lateral;
	
	int x, y, x2, y2;
	int *x1;
	int *y1;




};