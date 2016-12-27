#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>

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
	GLuint getProgram() { return programID;}
	~Shader();
	
private:
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


};


