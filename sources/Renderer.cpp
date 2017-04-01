#include "../headers/Renderer.h"
#include "../headers/Skybox.h"
#include <algorithm>

Renderer* Renderer::instance = nullptr;
/**************************************************************************************************************************************/
Renderer* Renderer::getInstance(){
	if (instance == nullptr)
		instance = new Renderer();
	return instance;
}


void Renderer::destroyPointersOnlyStatic(){
for (std::pair<Material*, std::vector<Mesh*>> &paire : dynamic_mesh_list)
	{
		for (Mesh* A : paire.second){
			delete A; 
		}
		delete paire.first; 
	}
}

void Renderer::destroyPointersOnlyDynamic(){


	for (std::pair<Material*, Mesh*> &paire : static_mesh_list){
		delete paire.second;
		delete paire.first;
	}
}


void Renderer::destroy(){
	for (std::pair<Material*, std::vector<Mesh*>> &paire : dynamic_mesh_list)
	{
		paire.first->clean();
		for (Mesh* A : paire.second){
			A->clean();
			delete A; 
		}
		delete paire.first; 
	}

	for (std::pair<Material*, Mesh*> &paire : static_mesh_list){
		paire.first->clean();
		paire.second->clean(); 
		delete paire.second;
		delete paire.first;
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

static void addDynamic(Mesh* A, std::vector<std::pair<Material*, std::vector<Mesh*>>> &dynamic_mesh_list){
	for (std::pair<Material*, std::vector<Mesh*>> &paire : dynamic_mesh_list){

		if (*paire.first == *A->getMaterial()){
			paire.second.push_back(A);
			return;
		}
	}

	std::vector<Mesh*> temp;
	temp.push_back(A);

	Material *M = new Material(*A->getMaterial());
	std::pair<Material*, std::vector<Mesh*>> paire(M, temp);
	dynamic_mesh_list.push_back(paire);

}

static Mesh* addStatic(Mesh* A , std::vector<std::pair<Material* , Mesh*>> &static_mesh_list){
	for (std::pair<Material*, Mesh*> &paire : static_mesh_list){

		if (*paire.first == *A->getMaterial()){
			paire.second->merge(*A);
			delete A;
			return paire.second;
		}
	}


	Material *M = new Material(*A->getMaterial());
	std::pair<Material*, Mesh*> paire(M, A);
	static_mesh_list.push_back(paire);
	return A;
}
void Renderer::addDynamicMesh(Mesh* A){ // construct mesh from here
	
	addDynamic(A, dynamic_mesh_list); 

}

void Renderer::addDynamicMeshes(std::vector<Mesh*> &A){
	for (Mesh* m : A)
		addDynamicMesh(m); 
	
}


/**************************************************************************************************************************************/

/**************************************************************************************************************************************/
void Renderer::renderDynamicMeshes(glm::mat4 projection ,  glm::mat4 view){
	auto lambda = [&](std::pair<Material*, std::vector<Mesh*>> &Elem){
		Elem.first->Bind();
		BaseShader* s =dynamic_cast<BaseShader*> (Elem.first->getShader());
		s->BindLights();
		for (Mesh* mesh : Elem.second)
			mesh->display_dynamic(projection, view , s); 
		Elem.first->Unbind();
	};
	for_each(dynamic_mesh_list.begin(), dynamic_mesh_list.end(), lambda);

}
/**************************************************************************************************************************************/

Mesh* Renderer::addStaticMesh(Mesh* A){
	return addStatic(A, static_mesh_list); 
}



/**************************************************************************************************************************************/


void Renderer::renderStaticMeshes(glm::mat4 projection,  glm::mat4 view){
	auto lambda = [&](std::pair<Material*, Mesh*> &Elem){
		Elem.first->Bind();
		BaseShader* s =dynamic_cast<BaseShader*> (Elem.first->getShader());
		s->BindLights();
			Elem.second->display_static(projection, view , s);
		Elem.first->Unbind();
	};
	for_each(static_mesh_list.begin(), static_mesh_list.end(), lambda);
}

/**************************************************************************************************************************************/


void Renderer::addStaticMeshes(std::vector<Mesh*> &A){
	for (Mesh* m : A)
		addStaticMesh(m);

}





/**************************************************************************************************************************************/


void Renderer::renderAll(glm::mat4& projection , glm::mat4 &view , Skybox *skybox){
	
	skybox->render(projection , view); 
	renderStaticMeshes(projection, view);
	renderDynamicMeshes(projection, view); 

}





/**************************************************************************************************************************************/
void Renderer::sort(){
	sortDynamic(); 
	sortStatic(); 
	sortGUI(); 

}
/**************************************************************************************************************************************/


void Renderer::sortDynamic( ){
	std::list<Mesh*> temp_meshes; 
	for (std::pair<Material* , std::vector<Mesh*>> &e : dynamic_mesh_list){
		Material* material = e.first; 
		std::vector<Mesh*>::iterator it = std::find_if(e.second.begin(), e.second.end(), [material](Mesh* M){
			return !(*M->getMaterial() == *material); 
		});

		if (it != e.second.end()){
			Mesh* temp = *it; 
			e.second.erase(it); 
			addDynamicMesh(temp); 

			return;
		}
	}

	
	 
	
	
}

void Renderer::sortStatic(){
	for (auto &e : static_mesh_list){
		Material* material = e.first; 
		Mesh * mesh = e.second; 
		if (!(*mesh->getMaterial() == *material)){
			addStaticMesh(mesh); 
			e.second = nullptr; 
		}
	}
	
}

void Renderer::sortGUI(){

}


void Renderer::addGui(std::vector<Mesh*> &mesh){

}

void Renderer::addGui(Mesh* M){

}


void Renderer::renderShadowMap(glm::mat4& projection, glm::mat4& view, Framebuffer& framebuffer , Shader* shader){
	framebuffer.BindDepth(); 
	shader->BindShader(); 
	for (std::pair<Material*, std::vector<Mesh*>> &e : dynamic_mesh_list){
		for (Mesh* mesh : e.second)
			mesh->display_dynamic(projection, view , shader); 

	}
	for (std::pair<Material*, Mesh*> &e : static_mesh_list)
		e.second->display_static(projection, view , shader); 
	shader->UnBindShader(); 
	framebuffer.Unbind();



}