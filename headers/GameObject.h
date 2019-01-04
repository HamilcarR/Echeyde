#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Constants.h"
#include "Mesh.h"

class Object{
public :
	Object(); 
	Object(std::vector<object_data> &list_mesh, Shader* s);

	virtual ~Object(); 
	virtual void translate(glm::vec3 t);
	virtual void rotate(float a, glm::vec3 rotation);
	virtual void scale(glm::vec3 scale);
	virtual void rotateAround(float angle, glm::vec3 target , glm::vec3 axis);
	virtual void onTerrain(float x , float z , geometry_data terrain) ;  
	Transform getTransform(){ return transform; }
	void isDisplayed(bool displayed); 
	std::vector<Mesh*> getMeshes(){ return mesh_list; }
	/*Set texture of one mesh*/
	virtual void setTexture(unsigned int mesh, Texture texture, Echeyde::TEX tex_unit); 
	/*Set texture for all meshes*/
	virtual void setTexture(Texture texture, Echeyde::TEX tex_unit); 
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
	bool isStatic(){ return m_isStatic;  }
	void addTexture(std::string file, std::string name); 

private:
	bool m_isStatic; 
};

#endif
