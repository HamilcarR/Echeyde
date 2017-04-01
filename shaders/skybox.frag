#version 450 compatibility


in vec3 Itex; 

uniform samplerCube diffuse ; 


out vec4 color ; 

void main(){
	vec3 tex = normalize(Itex);
	color = texture(diffuse , tex) ; 
}