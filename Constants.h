#ifndef CONSTANTS_H
#define CONSTANTS_H



#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <regex>
#include <memory>
#include <glm\common.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>
#include <cinttypes>
#include <thread>
#include <future>
#include <sstream>
#include <map>
#include <SDL\SDL.h>
#include <GL\glew.h>

#include <vector>


class Texture;

/*Paths*/
const std::string SHADER_LOCATION = "shaders/";
const std::string RESSOURCES_LOCATION = "res/";
const std::string TEXTURES_LOCATION = RESSOURCES_LOCATION + "textures/";


/****************************************************************************************************************************************************************************/
/*Constants*/
const uint16_t WIDTH = 800; 
const uint16_t HEIGHT = 800; 
const uint16_t EVENT_ARRAY_SIZE = 10; 
const int vbo_size = 7; 
const std::string M_PROJECTION = "projection";
const std::string M_MODEL = "model";
const std::string M_VIEW = "view";
static const char* shader_uniforms_texture_names[] = { "diffuse","normal","blendmap","specular","ambiant","height","dudv" };

/****************************************************************************************************************************************************************************/
/*Enums*/
namespace Echeyde {
	enum VBO : unsigned { VERTEX = 0, COLOR = 1, NORMAL = 2, TANGENT = 3, TEXTURE = 4,BITANGENT = 5, INDICE = 6   };
	enum TEX : unsigned { DIFFUSE0 = 0 , NORMAL0 = 1 , OPACITY0=2, BLENDMAP0 = 3 , SPECULAR0 = 4 , AMBIENT0 = 5 , HEIGHT0 = 6 , DUDV0 = 7 , OPTIONAL0 = 8 , OPTIONAL1 = 9 ,OPTIONAL2 = 10};
}


/****************************************************************************************************************************************************************************/
/*Data structs with their methods*/
struct vertex_data {
	glm::vec3 position; 
	glm::vec2 texture;
	glm::vec3 normal;
	glm::vec3 color;
};

/*******************/
struct geometry_data {
public:
	std::vector<float> vertex;
	std::vector<unsigned short> indices; 
	std::vector<float> texture;
	std::vector<float> normal; 
	std::vector<float> tangent; 
	std::vector<float> color; 
	std::vector<float> bitangent;
	void print(std::ofstream &file_o) {
		int rap = 1;
		file_o << "Vertices :\n";
		for (float m : vertex) {
			file_o << std::to_string(m) << ((rap % 3 == 0 ) ? "\n" : "    ");
			rap++;
		}
		rap = 1;
		file_o << "Normals :\n";
		for (float m : normal) {
			file_o << std::to_string(m) << ((rap % 3 == 0 ) ? "\n" : "    ");
			rap++;
		}
		file_o << "Colors :\n";
		rap = 1; 
		for (float m : color) {
			file_o << std::to_string(m) << ((rap % 3 == 0 ) ? "\n" : "    ");
			rap++;
		}
		rap = 1;
		file_o << "Tangents :\n";

		for (float m : tangent) {
			file_o << std::to_string(m) << ((rap % 3 == 0 ) ? "\n" : "    ");
			rap++;
		}
		rap = 1;
		file_o << "Bitangents :\n";

		for (float m : bitangent) {
			file_o << std::to_string(m) << ((rap % 3 == 0) ? "\n" : "    ");
			rap++;
		}
		file_o << "Indices :\n";
		rap = 1;
		for (float m : indices) {
			file_o << std::to_string(m) << ((rap % 3 == 0 ) ? "\n" : "    ");
			rap++;
		}
		rap = 1;
		file_o << "Textures :\n";

		for (float m : texture) {
			file_o << std::to_string(m) << ((rap % 2 == 0 ) ? "\n" : "    ");
			rap++;
		}
	}

	void listing(std::string& file) {
		std::ofstream file_o(file.c_str());
		std::string vertex_ok = (vertex.size() > 0) ? "Vertex array OK\n" : "No vertex data available\n";
		std::string indices_ok = (indices.size() > 0) ? "Indices array OK\n" : "No indices data available\n";
		std::string texture_ok = (texture.size() > 0) ? "Texture array OK\n" : "No texture data available\n";
		std::string normal_ok = (normal.size() > 0) ? "Normal array OK\n" : "No normal data available\n";
		std::string tangent_ok = (tangent.size() > 0) ? "Tangent array OK\n" : "No tangent data available\n";
		std::string bitangent_ok = (bitangent.size() > 0) ? "Bitangent array OK\n" : "No Bitangent data available\n";
		std::string color_ok = (color.size() > 0) ? "Color array OK\n" : "No color data available\n";
		std::string data_status = vertex_ok + indices_ok + texture_ok + normal_ok + tangent_ok + color_ok + bitangent_ok; 
		file_o << data_status <<"\n"; 
		print(file_o); 
		file_o.close(); 
	}
};

/*******************/

struct textures_data {
	std::string diffuse;
	std::string normal;
	std::string opacity;
	std::string distortion;
	std::string optional;
};

struct material_data {
	std::vector<int> name;
	float specular_strength;
	float specular_exponent;
	bool transparency;
	glm::vec3 ambient_color;
	glm::vec3 specular_color;
	textures_data textures;
	

	bool diffuse_empty() { return textures.diffuse.empty(); }
	bool normal_empty() { return textures.normal.empty(); }
	bool opacity_empty() { return (textures.opacity.empty()) ; }
	bool distortion_empty() { return (textures.distortion.empty()); }
	bool optional_empty() { return (textures.optional.empty()) ; }
};

/*******************/

struct object_data {
	geometry_data data; 
	material_data material;
};
/*******************/

struct uniform_struct {
	GLuint vertex_u;
	GLuint color_u;
	GLuint texture_u;
	GLuint tangent_u;
	GLuint normal_u;

};
/****************************************************************************************************************************************************************************/
/*basic 3D models*/
const std::vector<float> cube = {
	// front
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0
};


const std::vector<float> color = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0
};
const std::vector<unsigned short> indice = {// front
	0, 1, 2,
	2, 3, 0,
	// top
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 0, 3,
	3, 7, 4,
	// left
	4, 5, 1,
	1, 0, 4,
	// right
	3, 2, 6,
	6, 7, 3 };



#endif 