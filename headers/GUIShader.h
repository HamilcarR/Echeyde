#pragma once
#include "Shader.h"
class GUIShader : public Shader
{
public:
	GUIShader();
	GUIShader(std::string& vertex_shader, std::string& geometry_shader, std::string &fragment_shader); 
	virtual ~GUIShader();
};

