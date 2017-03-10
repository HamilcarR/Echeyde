#include "../headers/Renderer.h"

Renderer* Renderer::instance = nullptr;
/**************************************************************************************************************************************/
Renderer* Renderer::getInstance(){
	if (instance == nullptr)
		instance = new Renderer();
	return instance;
}

void Renderer::destroy(){
	for (std::pair<Material, std::vector<Mesh*>> &paire : dynamic_mesh_list)
	{
		paire.first.clean();
		for (Mesh* A : paire.second){
			A->clean();
			delete A; 
		}
	}

	for (std::pair<Material, Mesh*> &paire : static_mesh_list){
		paire.first.clean(); 
		paire.second->clean(); 
		delete paire.second;
	}
}
/**************************************************************************************************************************************/

Renderer::Renderer()
{
}
/**************************************************************************************************************************************/

Renderer::~Renderer()
{
	
}

/**************************************************************************************************************************************/
void Renderer::addDynamicMesh(Mesh* A){ // construct mesh from here
	
	for (std::pair<Material, std::vector<Mesh*>> &paire : dynamic_mesh_list){
		
		if (paire.first == *A->getMaterial()){
			paire.second.push_back(A);
			return;
		}
	}
	
	std::vector<Mesh*> temp;
		temp.push_back(A); 
		Material M = *A->getMaterial();
		std::pair<Material, std::vector<Mesh*>> paire(M, temp);
		dynamic_mesh_list.push_back(paire); 
	

}

void Renderer::addDynamicMeshes(std::vector<Mesh*> &A){
	for (Mesh* m : A)
		addDynamicMesh(m); 
	
}


/**************************************************************************************************************************************/

/**************************************************************************************************************************************/
void Renderer::renderDynamicMeshes(glm::mat4 projection ,  glm::mat4 view){
	auto lambda = [&](std::pair<Material, std::vector<Mesh*>> &Elem){
		Elem.first.Bind();
		BaseShader* s = Elem.first.getShader();
		s->BindLights();
		for (Mesh* mesh : Elem.second)
			mesh->display_dynamic(projection, view); 
		Elem.first.Unbind();
	};
	for_each(dynamic_mesh_list.begin(), dynamic_mesh_list.end(), lambda);

}
/**************************************************************************************************************************************/

Mesh* Renderer::addStaticMesh(Mesh* A){
	for (std::pair<Material, Mesh*> &paire : static_mesh_list){

		if (paire.first == *A->getMaterial()){
			paire.second->merge(*A);
			delete A;
			return paire.second;
		}
	}


	Material M = *A->getMaterial();
	std::pair<Material, Mesh*> paire(M, A);
	static_mesh_list.push_back(paire);
	return A;
}



/**************************************************************************************************************************************/


void Renderer::renderStaticMeshes(glm::mat4 projection,  glm::mat4 view){
	auto lambda = [&](std::pair<Material, Mesh*> &Elem){
		Elem.first.Bind();
		BaseShader* s = Elem.first.getShader();
		s->BindLights();
		s->BindMatrices(projection, view, Elem.second->getTransform()->getModelMatrix());
			Elem.second->display_static(projection, view);
		Elem.first.Unbind();
	};
	for_each(static_mesh_list.begin(), static_mesh_list.end(), lambda);
}

/**************************************************************************************************************************************/


void Renderer::addStaticMeshes(std::vector<Mesh*> &A){
	for (Mesh* m : A)
		addStaticMesh(m);

}





/**************************************************************************************************************************************/


void Renderer::renderAll(glm::mat4& projection , glm::mat4 &view){
	renderStaticMeshes(projection, view);
	renderDynamicMeshes(projection, view); 
}





/**************************************************************************************************************************************/