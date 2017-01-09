#version 450 compatibility
#define MAX_LIGHTS 10

in vec3 Icolor;
in vec2 Itex;
in vec3 Inorm;
in vec3 Ito_pointLights[MAX_LIGHTS];
in vec3 Ito_directionalLights[MAX_LIGHTS];
in vec3 Ito_spotLights[MAX_LIGHTS];
in vec3 fragPos;
out vec4 color; 


struct SpotLightArray{
	vec3 position;
	vec3 color;
	vec3 attenuation;
	float radius;
	float power;

};

struct PointlightArray{
	vec3 position ; 
	vec3 color ; 
	vec3 attenuation ; 
	float power; 
	float radius ; 

};

struct DirectionalLightArray{
	vec3 position ; 
	vec3 color;
	float power; 

};

uniform PointlightArray pointLights[MAX_LIGHTS]; 
uniform DirectionalLightArray directLights[MAX_LIGHTS]; 
uniform SpotLightArray spotLights[MAX_LIGHTS]; 
uniform unsigned int directional_lights_size;
uniform unsigned int point_lights_size; 
uniform unsigned int spot_lights_size; 
uniform sampler2D diffuse;
uniform sampler2D normal;





vec3 computePointLights(){
	vec3 result;
	vec3 normalized_normals = Inorm; 
	vec3 sum = vec3(0.); 
	for(int i = 0 ; i < point_lights_size ; i++){
		
		vec3 attenuation = pointLights[i].attenuation;
		float power = pointLights[i].power;
		vec3 color = pointLights[i].color; 
		float radius = pointLights[i].radius;
		vec3 position = pointLights[i].position;
		vec3 to_light = normalize(position - fragPos); 
		float dist = length(position - fragPos);
		float attenuation_calculated = attenuation.x + attenuation.y*dist + attenuation.z*dist*dist;
		float light_variation = clamp(dot(normalized_normals ,to_light ) , 0.0 , 1.0) ;
		result+= power * light_variation * color /attenuation_calculated;

	}
	return result;
}

void main(){
	vec4 Plight = vec4(computePointLights(),0.); 
	color = texture2D(diffuse,Itex)+Plight;

}
