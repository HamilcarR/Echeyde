#version 450 compatibility


layout(triangles) in;
layout(triangle_strip,max_vertices=3) out;

in vec3 col[] ;
out vec3 Icolor ;


void main(){
	gl_Position = gl_in[0].gl_Position ;
	Icolor = col[0]; 
    EmitVertex();

    gl_Position = gl_in[1].gl_Position ;
	
	Icolor = col[0]; 
    EmitVertex();

	gl_Position = gl_in[2].gl_Position ;
	 
	Icolor = col[0]; 
    EmitVertex();

    EndPrimitive();
 }