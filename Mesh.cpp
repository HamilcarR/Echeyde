#include "Mesh.h"
#include "Renderer.h"









Mesh::Mesh() {
	draw_mode = GL_STATIC_DRAW;
	displayed = false;

}

Mesh::Mesh(const Mesh& copy){
	data = copy.data;
	transform = copy.transform;
	draw_mode = copy.draw_mode;
	textured_model = copy.textured_model;
	material = copy.material; 
	displayed = copy.displayed;
	vao = copy.vao;
	for (int i = 0; i < vbo_size; i++)
		vbo[i] = copy.vbo[i];

	uniforms = copy.uniforms; 
}

Mesh::Mesh(geometry_data &data_arg , std::shared_ptr<Material> &mat , bool isdisplayed)
{
	data = data_arg;
	draw_mode = GL_STATIC_DRAW;
	if (mat->isTextured())
		textured_model = true;
	else
		textured_model = false;
	material = mat; 
	displayed = isdisplayed;
	
	initVAO(); 
	Bind();
	

	
}


Mesh::~Mesh()
{ 
	
	
}

void Mesh::clean(){
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbo_size, vbo);
}


void Mesh::merge(Mesh& B){
	assert(*getMaterial() == *B.getMaterial()); 
	geometry_data new_geometry = geometry_data::merge(getGeometry(), B.getGeometry()); 
	/*add transform*/
	data = new_geometry; 
	clean(); 
	initVAO(); 
	Bind(); 

}


void Mesh::initVAO() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(vbo_size, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, data.vertex.size() * sizeof(GLfloat), data.vertex.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::COLOR]);
	glBufferData(GL_ARRAY_BUFFER, data.color.size() * sizeof(GLfloat), data.color.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, data.normal.size() * sizeof(GLfloat), data.normal.data(), draw_mode);



	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TANGENT]);
	glBufferData(GL_ARRAY_BUFFER, data.tangent.size() * sizeof(GLfloat), data.tangent.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::BITANGENT]);
	glBufferData(GL_ARRAY_BUFFER, data.bitangent.size() * sizeof(GLfloat), data.bitangent.data(), draw_mode);



	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, data.texture.size() * sizeof(GLfloat), data.texture.data(), draw_mode);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[Echeyde::INDICE]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GLushort), data.indices.data(), draw_mode);
}



void Mesh::Bind()
{
	glBindVertexArray(vao);	

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::VERTEX]);
	glVertexAttribPointer(Echeyde::VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glEnableVertexAttribArray(Echeyde::VERTEX);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::COLOR]);
	glVertexAttribPointer(Echeyde::COLOR, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glEnableVertexAttribArray(Echeyde::COLOR);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::NORMAL]);
	glVertexAttribPointer(Echeyde::NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glEnableVertexAttribArray(Echeyde::NORMAL);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TANGENT]);
	glVertexAttribPointer(Echeyde::TANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glEnableVertexAttribArray(Echeyde::TANGENT);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::BITANGENT]);
	glVertexAttribPointer(Echeyde::BITANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);	
	glEnableVertexAttribArray(Echeyde::BITANGENT);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TEXTURE]);
	glVertexAttribPointer(Echeyde::TEXTURE, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Echeyde::TEXTURE);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[Echeyde::INDICE]); 

	glBindVertexArray(0);

}




void Mesh::Unbind() {
	
	glDisableVertexAttribArray(Echeyde::TEXTURE); 
	glDisableVertexAttribArray(Echeyde::BITANGENT);
	glDisableVertexAttribArray(Echeyde::TANGENT);
	glDisableVertexAttribArray(Echeyde::NORMAL);
	glDisableVertexAttribArray(Echeyde::COLOR);
	glDisableVertexAttribArray(Echeyde::VERTEX);

}



void Mesh::display_dynamic(glm::mat4 &projection, glm::mat4 &view) {

	if (displayed) {
		if (isTransparent()){
			glDisable(GL_CULL_FACE);
			Bind();
			getMaterial()->getShader()->BindMatrices(projection, view, transform.getModelMatrix());
			glBindVertexArray(vao);
			{

				glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_SHORT, 0);
			}
			glBindVertexArray(vao);
			Unbind();
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else{
			Bind();

			glBindVertexArray(vao);
			{

				glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_SHORT, 0);
			}
			glBindVertexArray(vao);
			Unbind();
		}
		
		

	}
}


void Mesh::display_static(glm::mat4 &projection, glm::mat4 &view) {

	if (displayed) {
		if (isTransparent()){
			glDisable(GL_CULL_FACE);

			Bind();

			glBindVertexArray(vao);
			{

				glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_SHORT, 0);
			}
			glBindVertexArray(vao);
			Unbind();
			glEnable(GL_CULL_FACE); 
			glCullFace(GL_BACK); 
		}
		else{
			Bind();

			glBindVertexArray(vao);
			{

				glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_SHORT, 0);
			}
			glBindVertexArray(vao);
			Unbind();
		}



	}
}


