#version 450 compatibility 
#define MAX_LIGHTS 10  

in vec2 Itex;
in vec3 Ito_pointLights[MAX_LIGHTS];
in vec3 Ito_directionalLights[MAX_LIGHTS];
in vec3 Ito_spotLights[MAX_LIGHTS];
in vec2 nTex; 
in vec3 Inorm;
in vec3 fragPos; 
in vec4 depthFragment ; 
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
uniform sampler2D optional; 
uniform sampler2D normal;
uniform sampler2D opacity;
uniform sampler2D blendMap;
uniform sampler2D shadowmap;
uniform float spec_exponent ; 
uniform float spec_power ;
uniform int isTextured ;







struct LightResult{
	vec3 diffuse;
	vec3 specular; 
	float shadow_bias[MAX_LIGHTS]; 

};










LightResult computeDirectionalLights(vec3 Inor){
	LightResult result;
	result.diffuse = vec3(0.); 
	result.shadow_bias[0] = 0.f;
	result.specular = vec3(0.); 
	vec3 normalized_normals = Inor; 
	vec3 sum = vec3(0.); 

	for(int i = 0 ; i < directional_lights_size ; i++){
		float power = directLights[i].power;
		vec3 color = directLights[i].color; 
		vec3 position = directLights[i].position;
		vec3 to_light = normalize(position); 
		float light_variation = max(dot( to_light,normalized_normals ) , 0.0 ) ;
		result.diffuse += power * light_variation * color;
		result.shadow_bias[i] = max(0.005 * (1. - dot(to_light , normalized_normals)),0.000001);
	}
	return result;

}


LightResult computePointLights(vec3 Inor){
	LightResult result;
	result.diffuse = vec3(0.); 
	result.specular = vec3(0.); 
	vec3 normalized_normals = Inor; 
	vec3 sum = vec3(0.); 
	for(int i = 0 ; i < point_lights_size ; i++){
		vec3 attenuation = pointLights[i].attenuation;
		float power = pointLights[i].power;
		vec3 color = pointLights[i].color; 
		float radius = pointLights[i].radius;
		vec3 position = pointLights[i].position;


		vec3 to_light = normalize( ( position - fragPos)); 
		float dist = length(to_light); 
		if(dist>radius){
			result.diffuse += 0 ; 
		}
		else{
				
			
		float attenuation_calculated = attenuation.x + attenuation.y*dist + attenuation.z*dist*dist;
		float light_variation = max(dot( to_light,normalized_normals ) , 0.0 ) ;
		result.diffuse += power * light_variation * color /attenuation_calculated;
		}

	}
	
	return result;
}

vec4 blend(){
	
	vec4 blendmap = texture2D(opacity , nTex); 
	float backTexAmount = 1 - (blendmap.r + blendmap.g + blendmap.b) ; 
	vec2 tiled = nTex * 200. ; 
	vec4 a = texture2D(diffuse , tiled) * blendmap.r; 
	vec4 b = texture2D(optional , tiled) * blendmap.g ; 
	vec4 c = texture2D(normal , tiled) * blendmap.b  ; 
	vec4 d = texture2D(blendMap, tiled) * backTexAmount;
	return a+b+c+d ; 

}

const float pas = 0.0001f ; 
const int s_size = 8102 ; 


void main(){
	
	vec3 nmap_normales= normalize ( Inorm ) ; 
	LightResult P = computePointLights(nmap_normales) ; 
	LightResult D = computeDirectionalLights(nmap_normales) ; 

	vec4 Plight = vec4(P.diffuse,0.);
	vec4 Dlight = vec4(D.diffuse,0.); 

	vec3 NDC =   ((depthFragment.xyz/depthFragment.w)+1)/2 ;
	vec4 s1 = texture2D(shadowmap , vec2(NDC.x,NDC.y)); 
	
	
	
	
	
	
	if(s1.z >= NDC.z - 0.001)//D.shadow_bias[0]) 
		color = blend()*(Plight+Dlight);
	else
		color = blend() * vec4(0.01) ;	
	

}
