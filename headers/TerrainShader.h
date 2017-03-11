#pragma once
#include "Shader.h"


class TerrainShader : public BaseShader
{
public:
	TerrainShader();
	TerrainShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader);
	
	virtual ~TerrainShader();


private:




};

