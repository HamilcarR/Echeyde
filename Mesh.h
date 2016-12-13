#pragma once
#include "View.h"
#include "Material.h"

class Mesh
{
public:
	Mesh(vertex_data &data , Material &material,bool isdisplayed);
	virtual ~Mesh();
	void display(glm::mat4 &projection_matrix, glm::mat4 &model_matrix, glm::mat4 &view); 
	
	bool isTransparent() { return transparency; }
	bool isDisplayed() { return displayed; }
   
	
protected:
	
	bool transparency; 
	bool displayed;
	vertex_data data; 
	Material material; 
	uniform_struct uniforms;
	GLuint vao; 
	GLuint vbo[vbo_size];
	Uint16 draw_mode;

private:
	void Bind();
	void Unbind(); 
	void initVAO();
};
