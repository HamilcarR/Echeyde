#include "../headers/GameObject.h"
#include "../headers/Renderer.h"



Object::Object(){

}

Object::Object(std::vector<object_data> &list_mesh, Shader* s){

}


Object::~Object(){

}


void Object::setTexture(Texture A, Echeyde::TEX texunit){
	for (Mesh* mesh : mesh_list){
		mesh->setTexture(A, texunit); 
	}
}

void Object::setTexture(unsigned int mesh, Texture A, Echeyde::TEX texunit){
	assert(mesh < mesh_list.size());
	mesh_list[mesh]->setTexture(A, texunit); 
}



void Object::translate(glm::vec3 &t){
	 transform.translate(t); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->translate(t);
	 }

}
 void Object::rotate(float a, glm::vec3 rotation){
	 transform.rotate(a, rotation); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->rotate(a, rotation);
	 }
 }
 void Object::scale(glm::vec3 scale){
	 transform.scale(scale); 
	 for (Mesh* m : mesh_list){
		 m->getTransform()->scale(scale);
	 }
 }

 void Object::rotateAround(float angle, glm::vec3 target , glm::vec3 axis){
	 transform.rotateAround(angle, target, axis); 
	 translate(transform.getPosition()); 
 }


 void Object::isDisplayed(bool k){
	 for (auto &e : mesh_list)
		 e->setDisplayed(k); 
	 
 }






/********************************************************************************************************************************************/
GameObject::GameObject(std::vector<object_data> &list_mesh, Shader* s,bool displayed , bool isStatic):Object(list_mesh , s){
	Renderer *instance = Renderer::getInstance(); 
	for (object_data i : list_mesh) {
		std::shared_ptr<Material> material = std::shared_ptr<Material>(new Material(dynamic_cast<BaseShader*>(s), i.material));
		Mesh* temp = new Mesh(i.data, material, displayed );
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


GameObject::GameObject() :Object()
{
}


GameObject::~GameObject()
{
}





 