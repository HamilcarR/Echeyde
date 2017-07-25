#version 450 compatibility
#define MAX_LIGHTS 10

in vec3 Icolor;
in vec2 Itex;
in vec3 Ito_pointLights[MAX_LIGHTS];
in vec3 Ito_directionalLights[MAX_LIGHTS];
in vec3 Ito_spotLights[MAX_LIGHTS];
in vec3 fragPos;
in vec3 camPosition;
in vec3 Inorm;
in mat3 tangmat; 
in mat4 model; 
out vec4 color; 


struct SpotLightArray{
	vec3 position;
	vec3 direction; 
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
uniform float spec_exponent ; 
uniform float spec_power ;
uniform int isTextured ;







struct LightResult{
	vec3 diffuse;
	vec3 specular; 


};



/*not tested*/
LightResult computeSpotLight(vec3 Inor){
vec3 toEye =normalize((camPosition - fragPos)) ; 
LightResult result;
result.diffuse = vec3(0.); 
result.specular = vec3(0.); 
vec3 normalized_normals = Inor; 
vec3 sum = vec3(0.); 
float final_spec_pow = spec_power ; 
for(int i = 0 ; i < spot_lights_size ; i++){
		
		vec3 attenuation = spotLights[i].attenuation;
		float power = spotLights[i].power;
		vec3 color = spotLights[i].color; 
		float radius = spotLights[i].radius;
		vec3 position = spotLights[i].position;
		float radius = spotLights[i].radius ; 
		float angle = spotLights[i].angle ; 
		vec3 to_light = normalize( ( position - fragPos)); 
		
		
		float angleFragment = acos(cos(dot(-to_light , normalize(direction) ))) ; 
		if(angleFragment > angle){
			power = 0 ; 
			final_spec_pow = 0 ; 
		}
			
		float dist = length((to_light));	
		float attenuation_calculated = attenuation.x + attenuation.y*dist + attenuation.z*dist*dist;
		float light_variation = max(dot( to_light,normalized_normals ) , 0.0 ) ;

		vec3 reflected_light = reflect(-to_light,normalized_normals);
		float specular_variation = max(dot(toEye , reflected_light) , 0. ) ; 
		float spec_result = pow(specular_variation , spec_exponent) ; 
		result.specular += final_spec_pow * spec_result * color;
		result.diffuse += power * light_variation * color /attenuation_calculated;

	}
	return result ;
}





LightResult computeDirectionalLights(vec3 Inor){
	vec3 toEye =normalize((camPosition - fragPos)) ; 
	LightResult result;
	result.diffuse = vec3(0.); 
	result.specular = vec3(0.); 
	vec3 normalized_normals = Inor; 
	vec3 sum = vec3(0.); 

	for(int i = 0 ; i < directional_lights_size ; i++){
		float power = directLights[i].power;
		vec3 color = directLights[i].color; 
		vec3 position = directLights[i].position;
		vec3 to_light = normalize(position); 
		float dist = length(position - fragPos);
		float light_variation = max(dot( to_light,normalized_normals ) , 0.0 ) ;
		result.diffuse += power * light_variation * color;

		vec3 reflected_light = reflect(-to_light,normalized_normals);
		float specular_variation = max(dot(toEye , reflected_light) , 0. ) ; 
		float spec_result = pow(specular_variation , spec_exponent) ; 
		result.specular += spec_power * spec_result * color;

	}
	return result;

}


LightResult computePointLights(vec3 Inor){
	vec3 toEye =normalize((camPosition - fragPos)) ; 
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
		float dist = length((to_light));
		float attenuation_calculated = attenuation.x + attenuation.y*dist + attenuation.z*dist*dist;
		float light_variation = max(dot( to_light,normalized_normals ) , 0.0 ) ;

		vec3 reflected_light = reflect(-to_light,normalized_normals);
		float specular_variation = max(dot(toEye , reflected_light) , 0. ) ; 
		float spec_result = pow(specular_variation , spec_exponent) ; 
		result.specular += spec_power * spec_result * color;
		result.diffuse += power * light_variation * color /attenuation_calculated;

	}
	
	return result;
}




void main(){
if(isTextured == 1){
	vec3 nmap_normales=tangmat*(normalize(2*texture2D(normal,Itex)-1)).rgb ;
	LightResult P = computePointLights(nmap_normales) ; 
	LightResult D = computeDirectionalLights(nmap_normales) ; 

	vec4 Plight = vec4(P.diffuse,0.);
	vec4 Pspec = vec4(P.specular,0.); 
	vec4 Dlight = vec4(D.diffuse,0.); 
	vec4 Dspec = vec4(D.specular,0.);
	
	color = texture2D(diffuse,Itex)*(Plight+Dlight) + (Pspec+Dspec);
	}
	else{
	vec3 nmap_normales = normalize(Inorm); 
	LightResult P = computePointLights(nmap_normales) ; 
	LightResult D = computeDirectionalLights(nmap_normales) ; 

	vec4 Plight = vec4(P.diffuse,0.);
	vec4 Pspec = vec4(P.specular,0.); 
	vec4 Dlight = vec4(D.diffuse,0.); 
	vec4 Dspec = vec4(D.specular,0.);
	color = (Plight+Dlight) + (Pspec+Dspec);

	   }
}
