#pragma once
#include "Constants.h"
#include <unordered_map>
#include "Shader.h"

class Texture
{
public:
	Texture(); 
	Texture(std::string &image);
	virtual ~Texture();
	virtual void clean();
	GLuint getTexture(); 
	virtual void Bind(Echeyde::TEX texture_type, Shader* shader);
	void Unbind(); 
	bool isInitialized();
	bool operator==(Texture &A) const;
	bool operator<(const Texture &A) const; 
	const std::string& getTextureFile() const { return texture; }
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
	virtual void clean();

	const std::shared_ptr<Texture> getDiffuse_textures() const  { return diffuse_textures; }
	const std::shared_ptr<Texture> getNormal_textures() const { return normal_textures; }
	const std::shared_ptr<Texture> getOpacity_textures() const { return opacity_textures; }
	const std::shared_ptr<Texture> getDistortion_textures() const { return distortion_textures; }
	const std::shared_ptr<Texture> getOptional_textures() const { return optional_textures; }
	const std::shared_ptr<Texture> getBlend_textures() const { return blend_textures; }

	bool operator==(TextureGroup &A) const;
	bool operator<(const TextureGroup &A) const; 
	void bindFirst(Shader* shader);
	void unbind();
	bool isInitialized();
	const material_data getMaterialData() const { return Mdata; }
private:

	material_data Mdata; 
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
	static void clean();
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