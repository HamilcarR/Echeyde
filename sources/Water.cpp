#include "../headers/Water.h"


Water::Water(std::vector<object_data> list_mesh, Shader* s, bool displayed, bool isStatic) : 
	GameObject(list_mesh , s , displayed ,isStatic )
{
	//TODO create water mesh from Mesh 

}


Water::~Water()
{
}
