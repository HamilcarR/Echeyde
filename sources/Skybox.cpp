#include "..\headers\Skybox.h"
#include <SOIL\SOIL.h>
#include "..\headers\TextureException.h"



 std::vector<float> cube = {
	// front
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	// back
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	-1.0, 1.0, -1.0
};


const std::vector<float> color = {
	// front colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0,
	// back colors
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	1.0, 1.0, 1.0
};
const std::vector<unsigned short> indice = {// front
	0, 1, 2,
	2, 3, 0,
	// top
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// bottom
	4, 0, 3,
	3, 7, 4,
	// left
	4, 5, 1,
	1, 0, 4,
	// right
	3, 2, 6,
	6, 7, 3 };


const unsigned short SIZE = 2000; 
Skybox::Skybox(std::string cubemap , SkyboxShader shade)
{
	
	cubemapID = SOIL_load_OGL_single_cubemap(cubemap.c_str(), SOIL_DDS_CUBEMAP_FACE_ORDER, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MIPMAPS);
	assert(cubemapID != 0); 
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	for (unsigned i = 0; i < cube.size(); i++)
		cube[i] *= SIZE; 
	glGenVertexArrays(1, &vao); 
	glGenBuffers(2, vbos); 
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, cube.size() * sizeof(GLfloat), cube.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indice.size() * sizeof(unsigned short), indice.data(), GL_STATIC_DRAW);
	loadBuffers(); 
	transform.scale(glm::vec3(1000, 1000, 1000)); 
	shader = shade; 
}


void Skybox::loadBuffers(){
	glBindVertexArray(vao); 

	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
	glBindVertexArray(0);
	
}

void Skybox::unLoadBuffers(){
	glDisableVertexAttribArray(0); 
}
Skybox::~Skybox()
{
	
	shader.clean(); 
}

void Skybox::clean(){
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(2, vbos);
	glDeleteTextures(1 , &cubemapID); 
	shader.clean(); 
}
void Skybox::Bind(){
	shader.BindShader(); 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);

	shader.BindTextures(Echeyde::DIFFUSE0); 
	
}

void Skybox::UnBind(){
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); 
	shader.UnBindShader(); 
}


void Skybox::render(ViewCamera& camera){
	glDisable(GL_CULL_FACE);
	Bind(); 
	shader.BindMatrices(camera.getProjectionMatrix(), camera.getViewMatrix(), glm::mat4(1.)); 
	shader.BindZParameters(camera.isPerspectiveProjection(), camera.getZNear(), camera.getZFar() , glm::mat4(1.));
	glBindVertexArray(vao);
	{
		glDrawElements(GL_TRIANGLES, indice.size(), GL_UNSIGNED_SHORT, 0); 
	}
	glBindVertexArray(0);
	unLoadBuffers();
	UnBind(); 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}