#pragma once
#include "Constants.h"
#include <unordered_map>


class Texture
{
public:
	Texture(); 
	Texture(std::string &image);
	virtual ~Texture();
	GLuint getTexture(); 
	virtual void Bind(Echeyde::TEX texture_type, GLuint programID);
	void Unbind(); 
	bool isInitialized();
	bool operator==(Texture &A);
	std::string& getTextureFile() { return texture; }
private:
	std::string texture;
	GLuint id; 
};


/*A TextureGroup is a N textures package that each mesh could own*/
class TextureGroup {
public:
	TextureGroup();
	TextureGroup(material_data &data);
	virtual ~TextureGroup();
	std::shared_ptr<Texture> getDiffuse_textures() { return diffuse_textures; }
	std::shared_ptr<Texture> getNormal_textures() { return normal_textures; }
	std::shared_ptr<Texture> getOpacity_textures() { return opacity_textures; }
	std::shared_ptr<Texture> getDistortion_textures() { return distortion_textures; }
	std::shared_ptr<Texture> getOptional_textures() { return optional_textures; }
	std::shared_ptr<Texture> getBlend_textures() { return blend_textures; }

	

	void bindFirst(GLuint programID);
	void unbind();
	bool isInitialized();
private:
	std::shared_ptr<Texture> diffuse_textures;
	std::shared_ptr<Texture> normal_textures;
	std::shared_ptr<Texture> opacity_textures;
	std::shared_ptr<Texture> blend_textures;
	std::shared_ptr<Texture> distortion_textures;
	std::shared_ptr<Texture> optional_textures;

	
};


/*Texture Array : Optimizing the number of textures in RAM , allowing only one instance of a texture...will be static*/

class TextureArray {

public : 
	static TextureArray* getUniqueInstance();
	static void destroy();

	/*if texture_file doesn't exist in database,will create
	*a new texture then return it...if it exists,return the existant texture
	*/
	std::shared_ptr<Texture> addOrReturn(std::string &texture_file);
	bool idUsed(unsigned int id);
	bool isLoadedTexture(std::string &file); 
	std::map<unsigned int , std::shared_ptr<Texture>> getArray() { return texture_array;  }
	bool erase(GLuint id);
protected:
	std::map<unsigned int , std::shared_ptr<Texture>> texture_array;
	static TextureArray* instance; 
	
	TextureArray();
	~TextureArray(); 

};