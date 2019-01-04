#include "../headers/SkyboxShader.h"


SkyboxShader::SkyboxShader() :Shader()
{
}

SkyboxShader::SkyboxShader(const char* vertex, const char* fragment) : Shader(std::string(vertex), std::string(fragment)){

}

SkyboxShader::~SkyboxShader()
{
}

