#pragma once
#include "Texture.h"
#include "SkyboxShader.h"
class Skybox
{
public:
	Skybox(); 
	Skybox(std::string cubemap , SkyboxShader shader);
	virtual ~Skybox();
	virtual void Bind(); 
	virtual void UnBind(); 
	virtual void clean(); 
	virtual void render(glm::mat4 projection , glm::mat4 camera_view_matrix); 
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

