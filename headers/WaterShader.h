#ifndef WATERSHADER_H
#define WATERSHADER_H
#include "Shader.h"
class WaterShader : public BaseShader
{
public:
	WaterShader(std::string vertex_shader, std::string fragment_shader, std::string geometry_shader);
	virtual ~WaterShader();
};

#endif
