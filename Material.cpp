#include "Material.h"



Material::Material() {

}

Material::Material(const Material &A){
	assert(shader != nullptr); 
	shader = A.getShader(); 
	material_data mdat = A.getTextureGroup().getMaterialData(); 
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(mdat)); 
	ambient_color = A.ambient_color;
	specular_color = A.specular_color;
	specular_exponent = A.specular_exponent;
	specular_power = A.specular_power; 
	reflectivity = A.reflectivity;
	transparency = A.transparency;


}

Material::Material(BaseShader *s)
{
	shader = s; 
}

Material::Material(BaseShader *s, TextureGroup &tex) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
	specular_exponent = 0.f;
	specular_power = 0.f;
	reflectivity = 0.f;
}

Material::Material(BaseShader *s, TextureGroup &tex, bool trans) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
	transparency = trans;
	specular_exponent = 0.f;
	specular_power = 0.f;
	reflectivity = 0.f;
}
Material::Material(BaseShader *s, material_data& data) {
	specular_exponent = data.specular_exponent;
	specular_power = data.specular_strength;
	reflectivity = 0.f;
	shader = s;
	transparency = data.transparency;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(data));
}

Material::~Material()
{
	

}

void Material::clean(){
	if (DEBUG_DESTRUCTOR)
		std::cout << "Material deleted" << std::endl;
	shader->clean();
	textures->clean();
	
}


const GLuint Material::getProgram() const {
	
	return shader->getProgram();
}

void Material::BindValues(){

}

void Material::Bind() {
	glUseProgram(shader->getProgram());
	if (isTextured())
		textures->bindFirst(shader);
	shader->BindMaterials(specular_power, specular_exponent,isTextured());
}


void Material::Unbind() {
	textures->unbind(); 
	glUseProgram(0);
}


bool Material::operator==(Material A){
	if (A.getShader() == getShader() && A.getTextureGroup() == *textures && specular_exponent == A.getSpecularExponent() &&
		reflectivity == A.getReflectivity() && specular_exponent == A.getSpecularExponent() && A.isTransparent() == transparency)
		return true;
	else
		return false;
}

bool Material::operator<(const Material &A) const {
	if (getProgram() < A.getProgram() || getTextureGroup() < A.getTextureGroup())
		return true;
	else
		return false;
}

Material& Material::operator=(Material &A){
	return A;

}