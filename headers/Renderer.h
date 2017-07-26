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
	 void renderAll(ViewCamera& camera ,  Skybox *skybox , ViewCamera shadowCam);
	 void renderStaticMeshes(ViewCamera& camera, ViewCamera shadowCam);
	 void renderDynamicMeshes(ViewCamera& camera, ViewCamera shadowCam); 
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

	/*new rendering way:*/
	std::vector<Shader, std::vector<Mesh*>> shader_list; 
	std::vector<TextureGroup, std::vector<Mesh*>> texture_list; 
	std::vector<Material, std::vector<Mesh*>> material_list; 



};

