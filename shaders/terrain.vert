#version 450 compatibility




layout(location=0) in vec3 vertex;
layout(location=1) in vec3 color;
layout(location=2) in vec3 normal;
layout(location=3) in vec3 tangent;
layout(location=4) in vec2 texture;
layout(location=5) in vec3 bitangent;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view; 


out vec2 tex ; 
out vec3 norm ; 
out vec3 frag; 
out vec2 Ntex; 

void main(){
	mat4 MVP = projection * view * model;
	frag = (model  * vec4(vertex, 1)).xyz;
	gl_Position = MVP * vec4(vertex,1.) ;
	Ntex = texture; 
	tex = texture * 40.;
	norm = normal ; 
}