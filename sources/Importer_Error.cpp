#include "../headers/Importer_Error.h"


Importer_Error::Importer_Error(Assimp::Importer importer,std::string filename) :std::runtime_error(std::string("Importer problem with error :\n") + importer.GetErrorString()+std::string(" at file : ")+filename)
{

}


Importer_Error::~Importer_Error()
{
}
