#version 450 compatibility


in vec3 Icolor;


out vec4 color; 




void main(){
	color = vec4(Icolor,1.);

}