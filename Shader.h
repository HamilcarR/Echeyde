#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include "Light.h"
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL4_PROTOTYPES 1
#endif // WIN32



class Shader
{
public:
	Shader();
	Shader(std::string &vertex_shader, std::string& fragment_shader); 
	Shader(std::string &vertex_shader,std::string &fragment_shader,std::string &geometry_shader,std::string &tesselation_shader);
	Shader(std::string &vertex_shader, std::string& fragment_shader,std::string& geometry_shader);
	const GLuint getProgram() const { return programID;}
	virtual ~Shader();
	bool operator==(const Shader A) const;
	const std::string getVertexShader()const { return vertex_shader_name; }
	const std::string getFragmentShader()const{ return fragment_shader_name; }
	const std::string getGeometryShader()const{ return geometry_shader_name; }
	const std::string getTesselationShader()const{ return tesselation_shader_name; }
	virtual void clean();
	virtual void BindMatrices(glm::mat4& projection, glm::mat4& view, glm::mat4& model) const;
	virtual void BindTextures(GLuint tex_index, const char* uniform_tex);
	const GLuint getUniformProjection()const{ return uniform_projection; }
	const GLuint getUniformView()const{ return uniform_view; }
	const GLuint getUniformModel()const{ return uniform_model; }
protected:
	void compile_shaders();
	void create_shaders(); 

	

	std::string vertex_shader_name; 
	std::string fragment_shader_name;
	std::string geometry_shader_name;
	std::string tesselation_shader_name;

	GLuint programID; 
	
	GLuint vertex_shader; 
	GLuint fragment_shader;
	GLuint geometry_shader;
	GLuint tesselation_shader;

	GLuint uniform_projection;
	GLuint uniform_view;
	GLuint uniform_model;
};
struct ShaderDLightUni {
	std::vector<GLuint> uni_positions;
	std::vector<GLuint> uni_colors;
	std::vector<GLuint> uni_power;
};

struct ShaderPLightUni {
	std::vector<GLuint> uni_positions;
	std::vector<GLuint> uni_colors;
	std::vector<GLuint> uni_power;
	std::vector<GLuint> uni_attenuation;
	std::vector<GLuint> uni_radius;


};


struct ShaderSLightUni{
	std::vector<GLuint> uni_positions;
	std::vector<GLuint> uni_colors;
	std::vector<GLuint> uni_power;
	std::vector<GLuint> uni_attenuation;
	std::vector<GLuint> uni_radius;
};

class BaseShader :
	public Shader
{
public:
	BaseShader();
	BaseShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader);
	BaseShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader, std::string &tesselation_shader);
	BaseShader(std::string &vertex_shader, std::string &fragment_shader);
	virtual ~BaseShader();
	
	virtual void BindLights();
	
private:
	
	LightArray *lightArray;
	ShaderDLightUni DLight_uni;
	ShaderPLightUni PLight_uni;
	ShaderSLightUni SLight_uni;
	
};