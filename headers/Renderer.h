#pragma once
#include "Mesh.h"
#include "Skybox.h"
#include "Framebuffer.h"
#include "Camera.h"

class Renderer
{
public:
	 static Renderer* getInstance(); 
	 void destroy(); 
	 void addDynamicMesh(Mesh* M); 
	 void addDynamicMeshes(std::vector<Mesh*> &meshes);
	 Mesh* addStaticMesh(Mesh* mesh);
	 void addStaticMeshes(std::vector<Mesh*> &meshes);
	 void addGui(std::vector<Mesh*> &meshes);
	 void addGui(Mesh* M); 
	 void renderAll(ViewCamera& camera ,  Skybox *skybox);
	 void renderStaticMeshes(ViewCamera& camera);
	 void renderDynamicMeshes(ViewCamera& camera); 
	 void destroyPointersOnlyDynamic(); 
	 void destroyPointersOnlyStatic(); 
	 void renderShadowMap(ViewCamera& camera , Framebuffer& framebuffer  , Shader* shader); 
	 void sortDynamic(); 
	 void sortStatic(); 
	 void sortGUI();
	 void sort(); 
private:
	Renderer();
	virtual ~Renderer();
	static Renderer* instance;
	std::vector<std::pair<Material*, Mesh*>> static_mesh_list;
	std::vector<std::pair<Material*, std::vector<Mesh*>>> dynamic_mesh_list;
	std::vector<std::pair<Material*, std::vector<Mesh*>>> GUI_list;


};

