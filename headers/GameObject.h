#pragma once
#include "Constants.h"
#include "Mesh.h"


class Object{
public :
	Object(); 
	Object(std::vector<object_data> &list_mesh, Shader* s);
	virtual ~Object(); 
	virtual void translate(glm::vec3 &t);
	virtual void rotate(float a, glm::vec3 rotation);
	virtual void scale(glm::vec3 scale);
	virtual void rotateAround(float angle, glm::vec3 target , glm::vec3 axis);
	Transform getTransform(){ return transform; }
	void isDisplayed(bool displayed); 
	std::vector<Mesh*> getMeshes(){ return mesh_list; }


protected: 
	std::vector<Mesh*> mesh_list;
	Transform transform; 

};










class GameObject
 : public Object{
public:
	GameObject();
	GameObject(std::vector<object_data> &list_mesh, Shader* s, bool displayed, bool isStatic);

	virtual ~GameObject();
	
	void addTexture(std::string& file, std::string& name); 

private:
	
};

