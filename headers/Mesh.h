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
	 void merge( Mesh &B);
	
	Mesh();
	Mesh(geometry_data &data , std::shared_ptr<Material> &material,bool isdisplayed);
	Mesh(const Mesh& A); 
	virtual ~Mesh();
	virtual void clean();
	void display_static(glm::mat4 &projection_matrix,  glm::mat4 &view); 
	void display_dynamic(glm::mat4 &projection_matrix, glm::mat4 &view);
	void addTexture(Echeyde::TEX texture_type, std::string& file, std::string& shader_variable_name); 
	bool isTransparent() { return material->isTransparent(); }
	bool isDisplayed() { return displayed; }
	uniform_matrix getUniforms(){ return uniforms; }
	std::shared_ptr<Material> getMaterial(){ return material; }
	geometry_data getGeometry(){ return data; }
	Transform* getTransform(){ return &transform;  }
	
protected:
	
	bool textured_model;
	bool displayed;
	geometry_data data; 
	std::shared_ptr<Material> material; 
	Transform transform; 
	uniform_matrix uniforms;
	GLuint vao; 
	GLuint vbo[vbo_size];
	Uint16 draw_mode;

	void Bind();
	void Unbind();
	void initVAO();
private:
	
};

