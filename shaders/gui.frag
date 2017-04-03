#version 450 compatibility

in vec4 position ; 
in vec2 uv; 
uniform sampler2D diffuse; 
uniform int isPerspective;
uniform vec2 Z_parameters ;
out vec4 color ; 




void main(){
	color = texture2D(diffuse , uv) ; 
}