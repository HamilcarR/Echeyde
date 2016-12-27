#version 450 compatibility


layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec3 col[] ;
in vec2 tex[] ; 

out vec3 Icolor ;
out vec2 Itex;

void main(){
	gl_Position = gl_in[0].gl_Position ;
	Icolor = col[0]; 
	Itex = tex[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ;
	Itex = tex[1];
	Icolor = col[0]; 
    EmitVertex();

	gl_Position = gl_in[2].gl_Position ;
	 Itex = tex[2];
	Icolor = col[0]; 
    EmitVertex();

    EndPrimitive();
 }