#pragma once
#include "Shader.h"
#include "Texture.h"

class StaticShader
{
public:
	StaticShader();
	virtual ~StaticShader();


private:
	Shader shader; 
	TextureGroup textures; 

};

