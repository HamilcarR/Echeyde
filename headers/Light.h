#pragma once
#include "Constants.h"
/*forward rendering lights */

struct base_light_data{
	glm::vec3 colour;
	glm::vec3 position;
	float power;
	base_light_data(){
		colour = glm::vec3(0.);
		position = glm::vec3(0.);
		power = 0.f;
	}

	base_light_data(glm::vec3 col, glm::vec3 pos, float pow){
		colour = col;
		position = pos;
		power = pow;
	}
};

struct shader_light_data{
	Echeyde::LIGHTTYPE type;
	base_light_data base;
	glm::vec3 attenuation;
	float radius;
};


class Light
{
public:
	Light(); 
	Light(base_light_data& A); 
	virtual ~Light() = 0; 
	virtual void setPostion(glm::vec3 position){ this->position = position; };
	virtual void setPower(float power){this->power = power;};
	virtual base_light_data getBaseData(){ return base_light_data(colour, position, power); };
	virtual shader_light_data getLightInfo () =0; 
	virtual glm::vec3 getPosition() { return position; };
	virtual glm::vec3 getColour() { return colour; }
	virtual float getPower() { return power; }
	virtual void setPosition(int x, int y, int z){ position = glm::vec3(x, y, z);  }
	virtual void setPosition(glm::vec3 pos){ position = pos; }

protected:
	glm::vec3 colour;
	glm::vec3 position; 
	float power; 
};

/*************************************************************************************************************************************************************/

class PointLight : public Light{
public :
	PointLight();
	PointLight(base_light_data &data , float radius , glm::vec3 attenuation);
	virtual ~PointLight();
	virtual glm::vec3 getAttenuation(){ return attenuation; }
	virtual float getRadius(){ return radius; }
	virtual void setAttenuatio(glm::vec3 attenuation){this->attenuation = attenuation;};
	virtual void setRadius(float radius) { this->radius = radius; };
	virtual shader_light_data getLightInfo();
protected :
	glm::vec3 attenuation;
	float radius; // need that for fragment shader optimization...

};

/*************************************************************************************************************************************************************/
class DirectionalLight : public Light{
public:

	DirectionalLight();
	DirectionalLight(base_light_data& data);
	virtual ~DirectionalLight(); 
	virtual shader_light_data getLightInfo();




protected:

};

/*************************************************************************************************************************************************************/
class SpotLight : public PointLight{
public:
	SpotLight();
	virtual ~SpotLight();
	virtual shader_light_data getLightInfo();



protected:

};


/*************************************************************************************************************************************************************/

class LightArray{

public :
	struct LightsSizes{
		unsigned int directionnal; 
		unsigned int point;
		unsigned int spot;
	};


	static LightArray* getInstance();
	void clean();
	std::vector<Light*> getLightArray();
	void addLight(Light* light); 
	void deleteLight(unsigned short index);
	LightsSizes getLightsSizes();
	void computeLightsSizes(); 
private:
	LightArray();
	std::vector<Light*> getArray(){ return light_array;  }
	virtual ~LightArray();
	std::vector<Light*> light_array;
	LightsSizes lights_sizes;
	static LightArray* instance;
};



