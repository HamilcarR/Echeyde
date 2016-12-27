#pragma once
#include "View.h"
#include "Material.h"


class Mesh
{

	struct uniform_matrix {
		int projection;
		int view;
		int model;
	};

public:
	Mesh();
	Mesh(geometry_data &data , std::shared_ptr<Material> &material,bool isdisplayed);
	virtual ~Mesh();
	void display(glm::mat4 &projection_matrix, glm::mat4 &model_matrix, glm::mat4 &view); 
	
	bool isTransparent() { return material->isTransparent(); }
	bool isDisplayed() { return displayed; }
   
	
protected:
	
	bool textured_model;
	bool displayed;
	geometry_data data; 
	std::shared_ptr<Material> material; 
	uniform_matrix uniforms;
	GLuint vao; 
	GLuint vbo[vbo_size];
	Uint16 draw_mode;

private:
	void Bind();
	void Unbind(); 
	void initVAO();
};

