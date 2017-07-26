#pragma once
#include "GameObject.h"
#include "GUIShader.h"
class GUI : public GameObject
{
public:
	GUI(std::vector<object_data> &data , BaseShader* S,bool isdisplayed , bool isStatic);
	virtual ~GUI();
};

