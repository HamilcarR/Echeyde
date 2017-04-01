#version 450 compatibility
#define MAX_LIGHTS 10

layout(location=0) in vec3 vertex;
layout(location=1) in vec3 color;
layout(location=2) in vec3 normal;
layout(location=3) in vec3 tangent;
layout(location=4) in vec2 texture;
layout(location=5) in vec3 bitangent;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view; 



out vec3 col;
out vec2 tex;
out vec3 fragLoc;
out vec3 camPos;
out vec3 norm;
out mat3 TANGMAT;
 out mat4 s_model;

void main(){
	mat4 MVP = projection*view*model;
	mat4 MV = view*model;
	s_model = model ; 
	gl_Position = MVP*vec4(vertex,1.); 
	col=color; 
	tex=vec2(texture.x , texture.y) ;
	vec3 nmapN = normalize((model * vec4(normal,1.)).xyz) ; 
	norm = nmapN;
	vec3 tangN = normalize((model * vec4(tangent, 1.)).xyz); 
	vec3 bitN = normalize((model * vec4(bitangent, 1.)).xyz); 

	tangN = normalize(tangN - dot(tangN , nmapN) * nmapN);
	TANGMAT = mat3(tangN.x , bitN.x , nmapN.x,
						tangN.y , bitN.y , nmapN.y,
						tangN.z , bitN.z , nmapN.z); 
	fragLoc =  ((model*(vec4(vertex,1.))).xyz);
	camPos =  ((inverse(view) * vec4(0. , 0. , 0. , 1.)).xyz );					

	
	
	

}
