#ifndef IMPORTER_ERROR_H
#define IMPORTER_ERROR_H
#include "Constants.h"
#include <assimp/Importer.hpp>

class Importer_Error :
	public std::runtime_error
{
public:
	Importer_Error(Assimp::Importer importer,std::string filename);
	virtual ~Importer_Error();
};

#endif
