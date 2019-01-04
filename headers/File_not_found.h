#ifndef FILE_NOT_FOUND_H
#define FILE_NOT_FOUND_H
#include "Constants.h"
class File_not_found :
	public std::runtime_error
{
public:
	File_not_found(); 
	File_not_found(std::string error);
	virtual ~File_not_found();
	


private:
};

#endif
