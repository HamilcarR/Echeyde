#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H
#include "Shader.h"
class SkyboxShader : public Shader
{
public:
	SkyboxShader(); 
	SkyboxShader(const char* vertexShader , const char* fragmentShader);
	virtual ~SkyboxShader();
};

#endif
