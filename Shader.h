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
	const GLuint getProgram() const { return programID;}
	virtual ~Shader();
	bool operator==(const Shader A) const;
	virtual void clean();
	const std::string getVertexShader()const { return vertex_shader_name; }
	const std::string getFragmentShader()const{ return fragment_shader_name; }
	const std::string getGeometryShader()const{ return geometry_shader_name; }
	const std::string getTesselationShader()const{ return tesselation_shader_name; }
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


