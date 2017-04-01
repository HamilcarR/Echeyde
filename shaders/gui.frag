#version 450 compatibility

in vec4 position ; 
in vec2 uv; 
uniform sampler2D diffuse; 

out vec4 color ; 


float linearize_Z(){

	return (2*0.1) / (5000.f + 0.1 - texture2D(diffuse , uv).x*(5000.f -0.1f)) ; 
}


void main(){
	 color =vec4(linearize_Z()); 
}