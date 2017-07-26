#version 450 compatibility
#define MAX_LIGHTS 10


layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec3 col[] ;
in vec2 tex[] ; 
in vec3 norm[]; 
in vec3 fragLoc[];
in vec3 camPos[];
in mat3 TANGMAT[];
in mat4 s_model[] ; 
in vec4 depth[];

out vec4 Idepth;
out vec3 Icolor ;
out vec2 Itex;
out vec3 Inorm;
out vec3 fragPos;
out vec3 camPosition;
out mat3 tangmat;
out mat4 model; 


void main(){
	gl_Position = gl_in[0].gl_Position ;
	Icolor = col[0]; 
	Itex = tex[0];
	Inorm = norm[0];
	fragPos = fragLoc[0]; 
	camPosition = camPos[0];
	Idepth = depth[0]; 
	tangmat = TANGMAT[0];
	model = s_model[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ;
	Itex = tex[1];
	Icolor = col[1]; 
	Inorm = norm[1];	
	fragPos = fragLoc[1]; 
	camPosition = camPos[1];
	tangmat = TANGMAT[1];
	model = s_model[1];
	Idepth = depth[1]; 
    EmitVertex();

	gl_Position = gl_in[2].gl_Position ;
	Itex = tex[2];
	Icolor = col[2]; 
	Idepth = depth[2]; 
	Inorm = norm[2];
	fragPos = fragLoc[2]; 
	camPosition = camPos[2];
	tangmat = TANGMAT[2];
	model = s_model[2];
    EmitVertex();

    EndPrimitive();
 }