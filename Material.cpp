#include "Material.h"



Material::Material() {

}


Material::Material(Shader &s)
{
	shader = s; 
}


Material::~Material()
{
}


GLuint Material::getProgram() {
	
	return shader.getProgram(); 
}


void Material::Bind() {
	glUseProgram(shader.getProgram()); 
}


void Material::Unbind() {

	glUseProgram(0);
}