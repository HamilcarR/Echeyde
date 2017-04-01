#include "..\headers\GUI.h"
#include "..\headers\Renderer.h"
#include "..\headers\GUIShader.h"
GUI::GUI(std::vector<object_data> &data, GUIShader* s, bool isdisplayed) : Object(data , dynamic_cast<Shader*>(s))
{
	Renderer *renderer = Renderer::getInstance(); 
	//cube.rotate(90, glm::vec3(1, 0, 0)); 
	for ( object_data &e : data){
		std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(dynamic_cast<GUIShader*>(s), e.material));
		Mesh* M = new Mesh(e.data, material, isdisplayed);
		renderer->addGui(M);
		mesh_list.push_back(M); 
	}

}


GUI::~GUI()
{



}
