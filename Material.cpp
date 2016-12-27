#include "Material.h"



Material::Material() {

}


Material::Material(Shader &s)
{
	shader = s; 
}

Material::Material(Shader &s, TextureGroup &tex) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
}

Material::Material(Shader &s, TextureGroup &tex,bool trans) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
	transparency = trans;
}
Material::Material(Shader &s, material_data& data) {
	shader = s;
	transparency = data.transparency;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(data));
}

Material::~Material()
{
}


GLuint Material::getProgram() {
	
	return shader.getProgram(); 
}


void Material::Bind() {
	glUseProgram(shader.getProgram()); 
	textures->bindFirst(getProgram()); 
}


void Material::Unbind() {
	textures->unbind(); 
	glUseProgram(0);
}