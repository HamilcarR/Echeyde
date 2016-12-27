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

out vec3 col ;
out vec2 tex;
void main(){
	gl_Position = projection*view*model*vec4(vertex,1.); 
	col=color; 
	tex=texture;
}
