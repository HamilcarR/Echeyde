#version 450 compatibility

in vec4 position ; 


uniform int isPerspective;
uniform vec2 Z_parameters ;
out vec4 color ; 

float linearize_Z(float depth){
float zNear = Z_parameters.x ; 
float zFar = Z_parameters.y ; 
	return (2*zNear	) / (zFar + zNear - depth*(zFar -zNear)) ; 
}

void main(){
/*for visualising depth buffer */

	/*if(isPerspective == 1){
		 gl_FragDepth = linearize_Z(gl_FragCoord.z) ;				
		 color = vec4(1.);
		 
		 } 
	else{
		gl_FragDepth = gl_FragCoord.z;
		color = vec4(1.); 
	}*/

	color=vec4(1.);
}