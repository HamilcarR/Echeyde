#pragma once
#include "Constants.h"
class TextureException :
	public std::runtime_error
{
public:
	TextureException(std::string& error);
	virtual ~TextureException();
};

