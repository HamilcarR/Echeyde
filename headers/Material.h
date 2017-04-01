#pragma once
#include "View.h"
#include "Shader.h"
#include "Texture.h"
class Material
{
public:
	Material();
	Material(Shader *shader);
	Material(Shader *shader, TextureGroup& textures);
	Material(Shader *shader, material_data& material_dat);
	Material(Shader *shader, TextureGroup& textures, bool transparency);
	Material( Material &A); 
	virtual ~Material();
	virtual void clean();
	const GLuint getProgram() const;
	void Unbind(); 
	void Bind();
	bool isTransparent() { return transparency; }
	bool isTextured() { return textures->isInitialized(); }
	bool operator==( Material &A); 
	bool operator<( Material &A) ;
	Material& operator=(Material& A);
	std::shared_ptr<TextureGroup> getTextureGroup() const { return textures; }
	Shader* getShader() const { return shader; }
	float getSpecularExponent(){ return specular_exponent; }
	float getReflectivity(){ return reflectivity;  }
	void setTexture(Texture A, Echeyde::TEX id){ textures->setTexture(A, id); }
private:
	
	void BindValues(); 
	
	
	Shader *shader; // pointer that
	glm::vec3 ambient_color;
	glm::vec3 specular_color;
	float specular_power;
	float specular_exponent;
	float reflectivity; 
	bool transparency; 
	std::shared_ptr<TextureGroup> textures;


};

