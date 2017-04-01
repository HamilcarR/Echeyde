#include "../headers/Material.h"



Material::Material() {

}

Material::Material(Material &A){
	assert(shader != nullptr); 
	shader = A.getShader(); 
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(*A.getTextureGroup())); 
	ambient_color = A.ambient_color;
	specular_color = A.specular_color;
	specular_exponent = A.specular_exponent;
	specular_power = A.specular_power; 
	reflectivity = A.reflectivity;
	transparency = A.transparency;


}

Material::Material(Shader *s)
{
	shader = s; 
}

Material::Material(Shader *s, TextureGroup &tex) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
	specular_exponent = 0.f;
	specular_power = 0.f;
	reflectivity = 0.f;
}

Material::Material(Shader *s, TextureGroup &tex, bool trans) {
	shader = s;
	textures = std::shared_ptr<TextureGroup>(new TextureGroup(tex));
	transparency = trans;
	specular_exponent = 0.f;
	specular_power = 0.f;
	reflectivity = 0.f;
}
Material::Material(Shader *s, material_data& data) {
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
	shader->BindShader(); 
	if (isTextured())
		textures->bindFirst(shader);
	shader->BindMaterials(specular_power, specular_exponent,isTextured());
}


void Material::Unbind() {
	textures->unbind(); 
	shader->UnBindShader(); 
}

//il se fout de ma gueule ce programme
bool Material::operator==(Material &A){
	bool equal_tex = *A.getTextureGroup() == *textures; 
	bool equal_shader = A.getShader() == getShader();
	
	if (equal_shader && equal_tex && specular_exponent == A.getSpecularExponent() &&
		reflectivity == A.getReflectivity() && specular_exponent == A.getSpecularExponent() && A.isTransparent() == transparency)
		return true;
	else
		return false;
}

bool Material::operator<( Material &A)  {
	if (getProgram() < A.getProgram() || getTextureGroup() < A.getTextureGroup())
		return true;
	else
		return false;
}

Material& Material::operator=(Material &A){
	return A;

}