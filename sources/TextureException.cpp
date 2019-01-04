#include "../headers/TextureException.h"



TextureException::TextureException(std::string error) : std::runtime_error(error + " texture not found!")
{
}


TextureException::~TextureException()
{
}
