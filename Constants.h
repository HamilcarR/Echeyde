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

#ifdef WIN32
#include <GL\glew.h>
#else
#define GL4_PROTOTYPES 1 
#endif
#include <vector>




/*Paths*/

const std::string SHADER_LOCATION = "shaders/";
const std::string RESSOURCES_LOCATION = "res/"; 
/*Constants*/
const uint16_t WIDTH = 800; 
const uint16_t HEIGHT = 800; 
const uint16_t EVENT_ARRAY_SIZE = 10; 
const int vbo_size = 6; 
const std::string M_PROJECTION = "projection";
const std::string M_MODEL = "model";
const std::string M_VIEW = "view";

/*Enums*/
namespace Echeyde {
	enum VBO : unsigned { VERTEX = 0, COLOR = 1, NORMAL = 2, TANGENT = 3, TEXTURE = 4, INDICE = 5   };
	enum IMP: unsigned {OBJ = 0 , COL = 1 }; //upload wavefront or collada file
}



/*Data structs*/

struct vertex_data {
	std::vector<float> vertex;
	std::vector<unsigned short> indices; 
	std::vector<float> texture;
	std::vector<float> normal; 
	std::vector<float> tangent; 
	std::vector<float> color; 
};

struct material_data {
	std::vector<int> name; 
};


struct object_data {
	vertex_data data; 
	material_data material; 
};

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

struct uniform_struct {
	GLuint vertex_u;
	GLuint color_u;
	GLuint texture_u;
	GLuint tangent_u;
	GLuint normal_u;

};



#endif