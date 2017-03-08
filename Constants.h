#ifndef CONSTANTS_H
#define CONSTANTS_H
#define LIGHTS_COUNT_SHADER 10


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
const std::string HEIGHTMAPS_LOCATION = TEXTURES_LOCATION + "heightmaps/"; 

/****************************************************************************************************************************************************************************/
/*Constants*/
const uint16_t WIDTH = 900; 
const uint16_t HEIGHT = 900; 
const uint16_t EVENT_ARRAY_SIZE = 10; 
const int vbo_size = 7; 
const std::string M_PROJECTION = "projection";
const std::string M_MODEL = "model";
const std::string M_VIEW = "view";





/****************************************************************************************************************************************************************************/
/*Debug vars*/
static const bool DEBUG_DESTRUCTOR = true; 


/****************************************************************************************************************************************************************************/
/*Enums*/
namespace Echeyde {
	enum VBO : unsigned { VERTEX = 0, COLOR = 1, NORMAL = 2, TANGENT = 3, TEXTURE = 4,BITANGENT = 5, INDICE = 6   };
	const unsigned int TEX_SIZE = 10;

	enum TEX : unsigned { DIFFUSE0 = 0 , NORMAL0 = 1 , OPACITY0=2, BLENDMAP0 = 3 , SPECULAR0 = 4 , AMBIENT0 = 5 , HEIGHT0 = 6 , DUDV0 = 7 , DATA0 = 8 , OPTIONAL0 = 9};
	enum LIGHTTYPE : unsigned { DIRECTIONAL = 0, POINT = 1, SPOT = 2 };

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
	std::vector<unsigned int> indices; 
	std::vector<float> texture;
	std::vector<float> normal; 
	std::vector<float> tangent; 
	std::vector<float> color; 
	std::vector<float> bitangent;



	static geometry_data merge(geometry_data data1, geometry_data data2){
		
		geometry_data result;
		result.vertex.reserve(data1.vertex.size() + data2.vertex.size());
		result.indices.reserve(data1.indices.size() + data2.indices.size());
		result.texture.reserve(data1.texture.size() + data2.texture.size());
		result.normal.reserve(data1.normal.size() + data2.normal.size());
		result.tangent.reserve(data1.tangent.size() + data2.tangent.size());
		result.color.reserve(data1.color.size() + data2.color.size());
		result.bitangent.reserve(data1.bitangent.size() + data2.bitangent.size());

		result.vertex.insert(result.vertex.end(), data1.vertex.begin(), data1.vertex.end());
		result.vertex.insert(result.vertex.end(), data2.vertex.begin(), data2.vertex.end());

		result.texture.insert(result.texture.end(), data1.texture.begin(), data1.texture.end());
		result.texture.insert(result.texture.end(), data2.texture.begin(), data2.texture.end());

		result.indices.insert(result.indices.end(), data1.indices.begin(), data1.indices.end());
		for (unsigned short i : data2.indices)
			result.indices.push_back(i+data1.vertex.size()/3); 

		result.normal.insert(result.normal.end(), data1.normal.begin(), data1.normal.end());
		result.normal.insert(result.normal.end(), data2.normal.begin(), data2.normal.end());

		result.tangent.insert(result.tangent.end(), data1.tangent.begin(), data1.tangent.end());
		result.tangent.insert(result.tangent.end(), data2.tangent.begin(), data2.tangent.end());

		result.color.insert(result.color.end(), data1.color.begin(), data1.color.end());
		result.color.insert(result.color.end(), data2.color.begin(), data2.color.end());

		result.bitangent.insert(result.bitangent.end(), data1.bitangent.begin(), data1.bitangent.end());
		result.bitangent.insert(result.bitangent.end(), data2.bitangent.begin(), data2.bitangent.end());
		return result;
	}












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
		for (unsigned long m : indices) {
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
struct texture_uniforms{
	std::string uniform; 
	GLuint programID; 
};


struct textures_data {
	std::string diffuse;
	std::string normal;
	std::string opacity;
	std::string blend;
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
	bool blend_empty() { return (textures.blend.empty()); }
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

namespace echeyde{
	namespace testing{
		const std::vector<float> cube = {
			// front
			-1.0, -1.0, 1.0,
			1.0, -1.0, 1.0,
			1.0, 1.0, 1.0,
			-1.0, 1.0, 1.0,
			// back
			-1.0, -1.0, -1.0,
			1.0, -1.0, -1.0,
			1.0, 1.0, -1.0,
			-1.0, 1.0, -1.0
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

	}
}

/****************************************************************************************************************************************************************************/
/**/


class Transform{

public:

	
	Transform(){
		translation = glm::vec3(0.); 
		rotation = glm::vec4(0.); 
		scaling = glm::vec3(1.);
		model = glm::mat4(1.); 
	}
	virtual ~Transform(){

	}

	virtual void translate(glm::vec3 trans){
		translation = trans;
		model = glm::translate(translation); 
	}

	virtual void scale(glm::vec3 scal){
		scaling = scal;
		model = glm::scale(scaling);
	}

	virtual void rotate(float angle, glm::vec3 direction){
		rotation = glm::vec4(direction, angle); 
		model = glm::rotate(angle, direction); 
	}

	virtual glm::vec3 getPosition(){
		return translation;
	}
	virtual glm::vec4 getRotation(){
		return rotation;
	}
	virtual glm::vec3 getScale(){
		return scaling; 
	}

	virtual glm::mat4 getModelMatrix(){
		return model;
	}

	glm::vec3 translation;
	glm::vec4 rotation;
	glm::vec3 scaling;

	glm::mat4 model;

};


#endif 