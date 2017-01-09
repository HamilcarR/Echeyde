#include "Light.h"
#include <exception>

LightArray *LightArray::instance = nullptr;

LightArray* LightArray::getInstance(){
	if (instance == nullptr)
		instance = new LightArray();
	return instance;
}

void LightArray::clean(){
	for (Light* M : light_array)
		delete M; 
	delete instance;
	instance = nullptr;

}

/***************************************************************************************************************************************************/
/*Base Light class*/

Light::Light(){
	position = colour = glm::vec3(0); 
	power = 0.f;
}


Light::Light(base_light_data& data){
	position = data.position;
	colour = data.colour;
	power = data.power;
}

Light::~Light(){

}







/***************************************************************************************************************************************************/
/*Point Light class*/

PointLight::PointLight() :Light(){
	radius = 0.F;
	attenuation = glm::vec3(0); 
}

PointLight::PointLight(base_light_data& data, float rd , glm::vec3 atten) : Light(data){
	radius = rd;
	attenuation = atten; 
}

PointLight::~PointLight(){

}

shader_light_data PointLight::getLightInfo()  {
	shader_light_data data;
	data.type = Echeyde::POINT;
	data.base = getBaseData(); 
	data.attenuation = attenuation;
	data.radius = radius; 
	return data; 
}
/***************************************************************************************************************************************************/
/*Directional Light class*/

DirectionalLight::DirectionalLight(base_light_data& data) : Light(data){

}

DirectionalLight::DirectionalLight() : Light(){

}
DirectionalLight::~DirectionalLight(){

}

shader_light_data DirectionalLight::getLightInfo()  {
	shader_light_data data;
	data.type = Echeyde::DIRECTIONAL;
	data.base = getBaseData();

	return data;
}

/***************************************************************************************************************************************************/
/*SpotLight class*/




SpotLight::SpotLight() : PointLight(){

}

SpotLight::~SpotLight(){

}


shader_light_data SpotLight::getLightInfo()  {
	shader_light_data data;
	data.type = Echeyde::SPOT;
	data.base = getBaseData();
	data.attenuation = attenuation;
	data.radius = radius;
	return data;
}

/***************************************************************************************************************************************************/
/*Light array class*/

LightArray::LightArray(){
	lights_sizes = LightsSizes();
}

LightArray::~LightArray(){

}

std::vector<Light*> LightArray::getLightArray(){
	 return light_array; 
}

void LightArray::addLight(Light* A){
	light_array.push_back(A);
	computeLightsSizes();
}

void LightArray::deleteLight(unsigned short index){
	assert(index < light_array.size()); 
	if (index < light_array.size())
		light_array.erase(light_array.begin() + index); 
	
	computeLightsSizes();
}

LightArray::LightsSizes LightArray::getLightsSizes(){
	return lights_sizes;
}

void LightArray::computeLightsSizes(){
	
	for (Light* light : light_array){
		shader_light_data data =  light->getLightInfo();
		lights_sizes.directionnal += (data.type == Echeyde::DIRECTIONAL) ? 1 : 0;
		lights_sizes.spot += (data.type == Echeyde::SPOT) ? 1 : 0;
		lights_sizes.point += (data.type == Echeyde::POINT) ? 1 : 0;

	
	}
}