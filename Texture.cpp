#include "Texture.h"
#include <SOIL\SOIL.h>
#include <assert.h>
#include "TextureException.h"

const bool INVERT_Y = true;

/*Texture Class*/
/******************************************************************************************************************************************************************************************/
Texture::Texture() {
	id = 0; 
	texture = ""; 
}
/************************************************************************************/

Texture::Texture(std::string& filename , bool invert_y)
{
	glGenTextures(1, &id); 
	int width = 0, height = 0; 
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == 0)
		throw TextureException(filename);
	else {
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -3.0);
		glBindTexture(GL_TEXTURE_2D, 0); 
	}
	
}


Texture::~Texture()
{
	glDeleteTextures(1, &id);

}
/************************************************************************************/

GLuint Texture::getTexture() {
	
	return id; 
}
/************************************************************************************/

void Texture::Bind(Echeyde::TEX tex_index , GLuint programID) {
	assert(id != 0);
	glUniform1i(glGetUniformLocation(programID, shader_uniforms_texture_names[tex_index]), tex_index);
	glActiveTexture(GL_TEXTURE0 + tex_index);
	glBindTexture(GL_TEXTURE_2D, id);

}
/************************************************************************************/

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

/************************************************************************************/
bool Texture::isInitialized() {
	return (id == 0 || texture.size()==0) ? false : true;
}








/*TextureGroup class*/
/******************************************************************************************************************************************************************************************/
TextureGroup::TextureGroup() {

}
/************************************************************************************/
TextureGroup::TextureGroup(material_data& mat) {
	textures_data textures = mat.textures; 
	try {
		for (std::string &diffuse : textures.diffuse) {

			diffuse_textures.push_back(std::shared_ptr<Texture>(new Texture(diffuse, INVERT_Y)));
		}
		for (std::string &normal : textures.normal) {
			normal_textures.push_back(std::shared_ptr<Texture>(new Texture(normal, INVERT_Y)));

		}
		for (std::string &opacity : textures.opacity) {
			opacity_textures.push_back(std::shared_ptr<Texture>(new Texture(opacity, INVERT_Y)));

		}
		for (std::string &distortion : textures.distortion) {
			distortion_textures.push_back(std::shared_ptr<Texture>(new Texture(distortion, INVERT_Y)));

		}
		for (std::string &optional : textures.optional) {
			optional_textures.push_back(std::shared_ptr<Texture>(new Texture(optional, INVERT_Y)));

		}
	}
	catch (TextureException &e) {
		std::cout << e.what() << std::endl;
	}
}



/************************************************************************************/


TextureGroup::~TextureGroup() {

}



/************************************************************************************/
bool TextureGroup::isEmpty() {
	if (diffuse_textures.empty() && normal_textures.empty() && distortion_textures.empty() && opacity_textures.empty() && optional_textures.empty())
		return true;
	else
		return false;
}

/************************************************************************************/

void TextureGroup::bindFirst(GLuint programID) {
	diffuse_textures[0]->Bind(Echeyde::DIFFUSE0, programID);
	normal_textures[0]->Bind(Echeyde::NORMAL0, programID);
	
}


void TextureGroup::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0); 
}
/*TextureArray class*/
/******************************************************************************************************************************************************************************************/