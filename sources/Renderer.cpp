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
void Renderer::renderDynamicMeshes(ViewCamera& camera, ViewCamera shadowCam){
	glm::mat4 depth = shadowCam.getProjectionMatrix()*shadowCam.getViewMatrix();
		auto lambda = [&](std::pair<Material*, std::vector<Mesh*>> &Elem){
			Elem.first->Bind();
			BaseShader* s =dynamic_cast<BaseShader*> (Elem.first->getShader());
			s->BindLights();
			s->BindZParameters(camera.isPerspectiveProjection(), camera.getZNear(), camera.getZFar(),depth);
			for (Mesh* mesh : Elem.second)
			mesh->display_dynamic(camera.getProjectionMatrix(), camera.getViewMatrix() , s , GL_BACK);
			Elem.first->Unbind();
			};
			for_each(dynamic_mesh_list.begin(), dynamic_mesh_list.end(), lambda);

	
	for_each(dynamic_mesh_list.begin(), dynamic_mesh_list.end(), lambda);


}
/**************************************************************************************************************************************/

Mesh* Renderer::addStaticMesh(Mesh* A){
	return addStatic(A, static_mesh_list); 
}



/**************************************************************************************************************************************/


void Renderer::renderStaticMeshes(ViewCamera& camera, ViewCamera shadowCam){
	glm::mat4 depth = shadowCam.getProjectionMatrix() * shadowCam.getViewMatrix();
	auto lambda = [&](std::pair<Material*, Mesh*> &Elem){
		Elem.second->getMaterial()->Bind();
		BaseShader* s =dynamic_cast<BaseShader*> (Elem.second->getMaterial()->getShader());
		s->BindLights();
		s->BindZParameters(camera.isPerspectiveProjection(), camera.getZNear(), camera.getZFar(),depth); 
			Elem.second->display_static(camera.getProjectionMatrix(), camera.getViewMatrix() , s , GL_BACK);
		Elem.second->getMaterial()->Unbind();
	};
	for_each(static_mesh_list.begin(), static_mesh_list.end(), lambda);
}

/**************************************************************************************************************************************/


void Renderer::addStaticMeshes(std::vector<Mesh*> &A){
	for (Mesh* m : A)
		addStaticMesh(m);

}





/**************************************************************************************************************************************/


void Renderer::renderAll(ViewCamera& camera , Skybox *skybox , ViewCamera cam){
	

	renderStaticMeshes(camera , cam);
	renderDynamicMeshes(camera,cam); 
	skybox->render(camera); 
}





/**************************************************************************************************************************************/
void Renderer::sort(){
	sortDynamic(); 
	sortGUI(); 

}
/**************************************************************************************************************************************/

//TODO fix problem here /
void Renderer::sortDynamic( ){
	Mesh* add = nullptr; 
	std::list<Mesh*> temp_meshes; 
	std::vector<std::pair<Material*, std::vector<Mesh*>>>::iterator *structure_iterator = nullptr; 
	std::vector<std::pair<Material*, std::vector<Mesh*>>>::iterator *structure_iterator_deletion = nullptr; 
	std::vector<Mesh*>::iterator *mesh_iterator = nullptr; 
	for (std::vector<std::pair<Material*, std::vector<Mesh*>>>::iterator it1 = dynamic_mesh_list.begin(); it1 != dynamic_mesh_list.end(); it1++){
		Material* material = (*it1).first;
		std::vector<Mesh*>::iterator it = std::find_if((*it1).second.begin(), (*it1).second.end(), [material](Mesh* M){
			return !(*M->getMaterial() == *material);
		});

		if (it != (*it1).second.end()){
			add = *it;
			(*it1).second.erase(it);
			addDynamicMesh(add); 
			return; 
		}
	}
	
	
}

void Renderer::sortStatic(){
	
	
}

void Renderer::sortGUI(){

}


void Renderer::addGui(std::vector<Mesh*> &mesh){

}

void Renderer::addGui(Mesh* M){

}


void Renderer::renderShadowMap(ViewCamera& camera, Framebuffer& framebuffer , Shader* shader){
	framebuffer.BindDepth(); 
	shader->BindShader(); 
	shader->BindZParameters(camera.isPerspectiveProjection(), camera.getZNear(), camera.getZFar() , glm::mat4(1.)); 
	for (std::pair<Material*, std::vector<Mesh*>> &e : dynamic_mesh_list){
		for (Mesh* mesh : e.second)
			mesh->display_dynamic(camera.getProjectionMatrix(), camera.getViewMatrix() , shader , GL_BACK); 

	}
	for (std::pair<Material*, Mesh*> &e : static_mesh_list)
		e.second->display_static(camera.getProjectionMatrix(), camera.getViewMatrix(), shader,GL_BACK); 
	shader->UnBindShader(); 
	framebuffer.Unbind();


}