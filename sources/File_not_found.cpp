#include "../headers/File_not_found.h"



File_not_found::File_not_found(std::string erro) : std::runtime_error(std::string("File : ")+erro+std::string(" not found!\n"))
{

}

File_not_found::File_not_found() :std::runtime_error("File not found !")
{

}

File_not_found::~File_not_found()
{
}


