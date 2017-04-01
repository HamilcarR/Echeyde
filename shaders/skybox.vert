#version 450 compatibility

layout(location=0) in vec3 vertex; 


uniform mat4 view ; 
uniform mat4 model ; 
uniform mat4 projection ; 


out vec3 Itex; 

void main(){
mat4 PV = view;
PV[3][0] = 0;
PV[3][1] = 0;
PV[3][2] = 0;
	vec4 v = projection * PV * vec4(vertex,1.) ; 
	Itex = vertex ; 
	gl_Position = v ; 

}