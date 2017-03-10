#pragma once
#include "Constants.h"
#include "Mesh.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::vector<object_data> &list_mesh, Shader* s, bool displayed, bool isStatic);
	GameObject(std::vector<object_data> &list_mesh, Shader* s, bool displayed, bool isTextured, bool isStatic );

	virtual ~GameObject();
	virtual void translate(glm::vec3 &t);
	virtual void rotate(float a, glm::vec3 rotation);
	virtual void scale(glm::vec3 scale);
	Transform getTransform(){ return transform; }
	void addTexture(std::string& file, std::string& name); 

private:
	std::vector<Mesh*> mesh_list;
	Transform transform; 
};

