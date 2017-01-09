#version 450 compatibility
#define MAX_LIGHTS 10

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 color;
layout(location=2) in vec3 normal;
layout(location=3) in vec3 tangent;
layout(location=4) in vec2 texture;
layout(location=5) in vec3 bitangent;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view; 


out vec3 col;
out vec2 tex;
out vec3 norm;
out vec3 fragLoc;


void main(){
	mat4 MVP = projection*view*model;
	gl_Position = MVP*vec4(vertex,1.); 
	col=color; 
	tex=texture;
	norm=(model * vec4(normal,0.)).xyz;
	fragLoc = (model*(vec4(vertex,1.))).xyz;

	
}
