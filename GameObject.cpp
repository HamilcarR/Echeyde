#include "GameObject.h"
#include "Renderer.h"


GameObject::GameObject(std::vector<object_data> &list_mesh, Shader* s,bool displayed , bool isStatic){
	Renderer *instance = Renderer::getInstance(); 
	for (object_data i : list_mesh) {
		std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(dynamic_cast<BaseShader*>(s), i.material));
		Mesh* temp = new Mesh(i.data, material, displayed);
		if (isStatic){
			Mesh* A = instance->addStaticMesh(temp);
			if (temp != A)
				temp = A; 
		}
		else
			instance->addDynamicMesh(temp);

		mesh_list.push_back(temp);
	}
}


GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}





 void GameObject::translate(glm::vec3 &t){
	 transform.translate(t); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->translate(t);
	 }

}
 void GameObject::rotate(float a, glm::vec3 rotation){
	 transform.rotate(a, rotation); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->rotate(a, rotation);
	 }
 }
 void GameObject::scale(glm::vec3 scale){
	 transform.scale(scale); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->scale(scale);
	 }
 }