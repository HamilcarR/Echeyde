#pragma once
#include "Texture.h"
#include "SkyboxShader.h"
#include "Camera.h"
class Skybox
{
public:
	Skybox(); 
	Skybox(std::string cubemap , SkyboxShader shader);
	virtual ~Skybox();
	virtual void Bind(); 
	virtual void UnBind(); 
	virtual void clean(); 
	virtual void render(ViewCamera& camera); 
protected:
	GLuint cubemapID; 
	Transform transform; 
	SkyboxShader shader; 
	GLuint vao; 
	GLuint vbos[2]; 
private:
	 void loadBuffers(); 
	 void unLoadBuffers(); 



};

