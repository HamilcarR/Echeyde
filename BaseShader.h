#pragma once
#include "Shader.h"
#include <glm\glm.hpp>
class BaseShader :
	public Shader
{
public:
	BaseShader();
	BaseShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader);
	BaseShader(std::string &vertex_shader, std::string &fragment_shader); 
	virtual ~BaseShader();


private:
	GLuint uniform_projection;
	GLuint uniform_view;
	GLuint uniform_model;


};

