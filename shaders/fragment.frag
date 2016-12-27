#version 450 compatibility


in vec3 Icolor;
in vec2 Itex;



uniform sampler2D diffuse;
uniform sampler2D normal;




out vec4 color; 




void main(){
	color = texture2D(diffuse,Itex);

}