#pragma once
#include "Constants.h"



class Texture
{
public:
	Texture(); 
	Texture(std::string &image , bool invert_y);
	virtual ~Texture();
	GLuint getTexture(); 
	virtual void Bind(Echeyde::TEX texture_type, GLuint programID);
	void Unbind(); 
	bool isInitialized();
private:
	std::string texture;
	GLuint id; 
};

class TextureGroup {
public:
	TextureGroup();
	TextureGroup(material_data &data);
	virtual ~TextureGroup();
	std::vector<std::shared_ptr<Texture>> getDiffuse_textures() { return diffuse_textures; }
	std::vector<std::shared_ptr<Texture>> getNormal_textures() { return normal_textures; }
	std::vector<std::shared_ptr<Texture>> getOpacity_textures() { return opacity_textures; }
	std::vector<std::shared_ptr<Texture>> getDistortion_textures() { return distortion_textures; }
	std::vector<std::shared_ptr<Texture>> getOptional_textures() { return optional_textures; }

	std::shared_ptr<Texture> getNormal_texture(unsigned int pos) { if (pos < normal_textures.size() && pos>0) return normal_textures[pos]; else return std::shared_ptr<Texture>(); }
	std::shared_ptr<Texture> getDiffuse_texture(unsigned int pos) { if (pos < diffuse_textures.size() && pos>0) return diffuse_textures[pos]; else return std::shared_ptr<Texture>(); }
	std::shared_ptr<Texture> getOpacity_texture(unsigned int pos) { if (pos < opacity_textures.size() && pos>0) return opacity_textures[pos]; else return std::shared_ptr<Texture>(); }
	std::shared_ptr<Texture> getDistortion_texture(unsigned int pos) { if (pos < distortion_textures.size() && pos>0) return distortion_textures[pos]; else return std::shared_ptr<Texture>(); }
	std::shared_ptr<Texture> getOptional_texture(unsigned int pos) { if (pos < optional_textures.size() && pos>0) return optional_textures[pos]; else return std::shared_ptr<Texture>(); }

	void bindFirst(GLuint programID);
	void unbind();
	bool isEmpty();
private:
	std::vector<std::shared_ptr<Texture>> diffuse_textures;
	std::vector<std::shared_ptr<Texture>> normal_textures;
	std::vector<std::shared_ptr<Texture>> opacity_textures;
	std::vector<std::shared_ptr<Texture>> distortion_textures;
	std::vector<std::shared_ptr<Texture>> optional_textures;

	
};