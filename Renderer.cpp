#include "Renderer.h"

Renderer* Renderer::instance = nullptr;
/**************************************************************************************************************************************/
Renderer* Renderer::getInstance(){
	if (instance == nullptr)
		instance = new Renderer();
	return instance;
}

void Renderer::destroy(){
	for (std::pair<Material, std::vector<Mesh>> &paire : dynamic_mesh_list)
	{
		paire.first.clean();
		for (Mesh &A : paire.second)
			A.clean();
	}

	for (std::pair<Material, Mesh> &paire : static_mesh_list){
		paire.first.clean(); 
		paire.second.clean(); 
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
void Renderer::addDynamicMesh(Mesh &A){ // construct mesh from here
	
	for (std::pair<Material, std::vector<Mesh>> &paire : dynamic_mesh_list){
		
		if (paire.first == *A.getMaterial()){
			paire.second.push_back(A);
			return;
		}
	}
	
		std::vector<Mesh> temp; 
		temp.push_back(A); 
		Material M = *A.getMaterial();
		std::pair<Material, std::vector<Mesh>> paire(M, temp); 
		dynamic_mesh_list.push_back(paire); 
	

}

void Renderer::addDynamicMeshes(std::vector<Mesh> &A){
	for (Mesh& m : A)
		addDynamicMesh(m); 
	
}

void Renderer::addDynamicMeshes(std::vector<object_data> &list_mesh, Shader& s, bool displayed){
	std::vector<Mesh> meshes; 
	for (object_data i : list_mesh) {
		std::shared_ptr<Material> material =std::shared_ptr<Material>(new Material(s, i.material));
		meshes.push_back(Mesh(i.data, material, displayed));
	}
	addDynamicMeshes(meshes);
	
}
/**************************************************************************************************************************************/

/**************************************************************************************************************************************/
void Renderer::renderDynamicMeshes(glm::mat4 projection , glm::mat4 model , glm::mat4 view){
	auto lambda = [&](std::pair<Material , std::vector<Mesh>> &Elem){
		Elem.first.Bind();
		for (Mesh &mesh : Elem.second)
			mesh.display(projection, model, view); 
		Elem.first.Unbind();
	};
	for_each(dynamic_mesh_list.begin(), dynamic_mesh_list.end(), lambda);

}
/**************************************************************************************************************************************/

void Renderer::addStaticMesh(Mesh& A){
	for (std::pair<Material, Mesh> &paire : static_mesh_list){

		if (paire.first == *A.getMaterial()){
			//assert(*paire.second.getMaterial() == *A.getMaterial()); 
			paire.second.merge(A);
			return;
		}
	}


	Material M = *A.getMaterial();
	std::pair<Material, Mesh> paire(M, A);
	static_mesh_list.push_back(paire);
}



/**************************************************************************************************************************************/


void Renderer::renderStaticMeshes(glm::mat4 projection, glm::mat4 model, glm::mat4 view){
	auto lambda = [&](std::pair<Material, Mesh> &Elem){
		Elem.first.Bind();
			Elem.second.display(projection, model, view);
		Elem.first.Unbind();
	};
	for_each(static_mesh_list.begin(), static_mesh_list.end(), lambda);
}

/**************************************************************************************************************************************/


void Renderer::addStaticMeshes(std::vector<Mesh> &A){
	for (Mesh& m : A)
		addStaticMesh(m);

}

void Renderer::addStaticMeshes(std::vector<object_data> &list_mesh, Shader& s, bool displayed){
	std::vector<Mesh> meshes;
	for (object_data i : list_mesh) {
		std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(s, i.material));
		meshes.push_back(Mesh(i.data, material, displayed));
	}
	addStaticMeshes(meshes);

}




/**************************************************************************************************************************************/








/**************************************************************************************************************************************/