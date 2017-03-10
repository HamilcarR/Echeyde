#pragma once
#include "Constants.h"
class MaterialException :
	public std::runtime_error
{
public:
	MaterialException(); 
	MaterialException(std::string& err);
	virtual ~MaterialException();
};

