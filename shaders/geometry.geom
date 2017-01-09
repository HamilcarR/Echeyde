#version 450 compatibility
#define MAX_LIGHTS 10


layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec3 col[] ;
in vec2 tex[] ; 
in vec3 norm[]; 
in vec3 fragLoc[];



out vec3 Icolor ;
out vec2 Itex;
out vec3 Inorm;
out vec3 fragPos;





void main(){
	gl_Position = gl_in[0].gl_Position ;
	Icolor = col[0]; 
	Itex = tex[0];
	Inorm = norm[0];
	fragPos = fragLoc[0]; 
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ;
	Itex = tex[1];
	Icolor = col[1]; 
	Inorm = norm[1];	
	fragPos = fragLoc[1]; 
    EmitVertex();

	gl_Position = gl_in[2].gl_Position ;
	Itex = tex[2];
	Icolor = col[2]; 
	Inorm = norm[2];
	fragPos = fragLoc[2]; 
    EmitVertex();

    EndPrimitive();
 }