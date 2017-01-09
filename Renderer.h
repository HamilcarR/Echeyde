#pragma once
#include "Mesh.h"



class Renderer
{
public:
	static Renderer* getInstance(); 
	 void destroy(); 
	void addDynamicMesh(Mesh& M);
	void addDynamicMeshes(std::vector<Mesh> &meshes);
	void addDynamicMeshes(std::vector<object_data> &list_mesh, Shader* s, bool displayed);
	void addStaticMesh(Mesh &mesh);
	void addStaticMeshes(std::vector<Mesh> &meshes);
	void addStaticMeshes(std::vector<object_data> &list_mesh, Shader* s, bool displayed);
	void renderAll();
	void renderStaticMeshes(glm::mat4 projection, glm::mat4 model , glm::mat4 view);
	void renderDynamicMeshes(glm::mat4 projection, glm::mat4 model , glm::mat4 view); 

private:
	Renderer();
	virtual ~Renderer();
	static Renderer* instance;
	std::vector<std::pair<Material , Mesh>> static_mesh_list;
	std::vector<std::pair<Material, std::vector<Mesh>>> dynamic_mesh_list;
	std::vector<std::pair<Material, std::vector<Mesh>>> GUI_list;
	std::vector<std::shared_ptr<Mesh>> test;


};

