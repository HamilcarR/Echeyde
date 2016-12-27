#pragma once
#include "View.h"
#include "Shader.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(Shader &shader);
	Material(Shader &shader, TextureGroup& textures);
	Material(Shader &shader, material_data& material_dat);
	Material(Shader &shader, TextureGroup& textures,bool transparency);
	virtual ~Material();
	GLuint getProgram();
	void Unbind(); 
	void Bind();
	bool isTransparent() { return transparency; }
	bool isTextured() { return !textures->isEmpty(); }
private:
	Shader shader;
	glm::vec3 ambient_color;
	glm::vec3 specular_color;
	float specular_exponent;
	float reflectivity; 
	bool transparency; 
	std::shared_ptr<TextureGroup> textures;


};

