#pragma once
#include "View.h"
#include "Shader.h"
class Material
{
public:
	Material();
	Material(Shader &shader);
	virtual ~Material();
	GLuint getProgram();
	void Unbind(); 
	void Bind();
private:
	Shader shader;
};

