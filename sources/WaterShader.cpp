#include "..\headers\WaterShader.h"


WaterShader::WaterShader(std::string &vertex_shader, std::string &fragment_shader, std::string &geometry_shader) 
	: BaseShader(vertex_shader , fragment_shader , geometry_shader)
{



}


WaterShader::~WaterShader()
{
}
