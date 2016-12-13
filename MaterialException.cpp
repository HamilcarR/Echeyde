#include "MaterialException.h"



MaterialException::MaterialException(std::string &err):std::runtime_error(std::string("Material : " )+err+std::string(" not found!"))
{
}
MaterialException::MaterialException() : std::runtime_error("Mtllib not found in .obj file") {

}

MaterialException::~MaterialException()
{
}
