#version 450 compatibility
#define MAX_LIGHTS 10


layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec2 tex[] ; 
in vec3 norm[]; 
in vec3 frag[]; 
in vec2 Ntex[];
in vec4 depthfragment[];

out vec4 depthFragment;
out vec2 Itex;
out vec3 Inorm;
out vec3 fragPos; 
out vec2 nTex; 

void main(){
	gl_Position = gl_in[0].gl_Position ;
	Itex = tex[0]; 
	Inorm = norm[0];	
	fragPos = frag[0]; 
	nTex = Ntex[0];
	depthFragment = depthfragment[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ;
	nTex = Ntex[1];
	Itex = tex[1];
	Inorm = norm[1];	
	fragPos= frag[1]; 
	depthFragment = depthfragment[1];
    EmitVertex();

	gl_Position = gl_in[2].gl_Position ;
	nTex = Ntex[2];
	Itex = tex[2];
	Inorm = norm[2];
	fragPos= frag[2]; 
	depthFragment = depthfragment[2];
    EmitVertex();

    EndPrimitive();
 }