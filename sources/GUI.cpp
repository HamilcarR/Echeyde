#include "..\headers\GUI.h"
#include "..\headers\Renderer.h"
#include "..\headers\GUIShader.h"

GUI::GUI(std::vector<object_data> &data, BaseShader* s, bool isdisplayed , bool isStatic) : GameObject(data , s , isdisplayed , isStatic)
{
	
	rotate(90, glm::vec3(1, 0, 0)); 

	
}


GUI::~GUI()
{



}
