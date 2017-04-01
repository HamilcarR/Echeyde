#pragma once
#include "GameObject.h"
class Water : public GameObject
{
public:
	Water(std::vector<object_data> &list_mesh, Shader* s, bool displayed,  bool isStatic);
	virtual ~Water();
};

