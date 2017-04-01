#pragma once
#include "GameObject.h"
#include "GUIShader.h"
class GUI : public Object
{
public:
	GUI(std::vector<object_data> &data , GUIShader* S,bool isdisplayed);
	virtual ~GUI();
};

