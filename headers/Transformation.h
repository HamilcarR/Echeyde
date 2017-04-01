#pragma once
#include "Constants.h"

class Transform{

public:

	
	Transform(){
		translation = glm::vec3(0.); 
		rotation = glm::vec4(0.); 
		rotation.y = 1; 
		scaling = glm::vec3(1.);
		model = glm::mat4(1.); 
	}
	virtual ~Transform(){

	}

	virtual void translate(glm::vec3 trans){
		translation = trans;
	}

	virtual void scale(glm::vec3 scal){
		scaling = scal;
	}

	virtual void rotate(float angle, glm::vec3 direction){
		rotation = glm::vec4(direction, angle); 
	}

	virtual glm::vec3 getPosition(){
		return translation;
	}
	virtual glm::vec4 getRotation(){
		return rotation;
	}
	virtual glm::vec3 getScale(){
		return scaling; 
	}
	
	virtual glm::mat4 getModelMatrix(){
		resetMatrix(); 
		model = glm::translate(model, translation); 
		model = glm::rotate(model, glm::radians(rotation.a), glm::vec3(rotation.r, rotation.g, rotation.b));
		model = glm::scale(model,scaling);

		return model;
	}
	virtual void resetMatrix(){
		model = glm::mat4(1.); 
	}
	virtual void rotateAround(float angle, glm::vec3 target , glm::vec3 axis){
		glm::vec3 position = translation;
		glm::vec3 var = position - target;
		glm::vec3 newPosition = glm::rotate(var, angle, axis);
		translate(newPosition);
	}
protected : 

	glm::vec3 translation;
	glm::vec4 rotation;
	glm::vec3 scaling;

	glm::mat4 model;

};

