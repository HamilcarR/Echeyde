#include "Mesh.h"



Mesh::Mesh(vertex_data &dat , Material &mat , bool isdisplayed)
{
	draw_mode = GL_STATIC_DRAW;
	for (int v : dat.indices)
		data.indices.push_back(v); 
	for (float v : dat.vertex) 
		data.vertex.push_back(v); 
	for (float v : dat.color)
		data.color.push_back(v);
	for (float v : dat.normal)
		data.normal.push_back(v);
	for (float v : dat.texture)
		data.texture.push_back(v);
	for (float v : dat.tangent)
		data.tangent.push_back(v);
	GLuint program = mat.getProgram();
	material = mat; 
	displayed = isdisplayed;
	initVAO();
	Bind(); 
}


Mesh::~Mesh()
{
}





void Mesh::initVAO() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(vbo_size, vbo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::VERTEX]); 
	glBufferData(GL_ARRAY_BUFFER, data.vertex.size() * sizeof(GL_FLOAT), data.vertex.data(), draw_mode );

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::COLOR]);
	glBufferData(GL_ARRAY_BUFFER, data.color.size() * sizeof(GL_FLOAT), data.color.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, data.normal.size() * sizeof(GL_FLOAT), data.normal.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TANGENT]);
	glBufferData(GL_ARRAY_BUFFER, data.tangent.size() * sizeof(GL_FLOAT), data.tangent.data(), draw_mode);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, data.texture.size() * sizeof(GL_FLOAT), data.texture.data(), draw_mode);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[Echeyde::INDICE]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(GL_UNSIGNED_SHORT), data.indices.data(), draw_mode);
	
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

	glBindBuffer(GL_ARRAY_BUFFER, vbo[Echeyde::TEXTURE]);
	glVertexAttribPointer(Echeyde::TEXTURE, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(Echeyde::TEXTURE);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[Echeyde::INDICE]); 

	glBindVertexArray(0); 

}




void Mesh::Unbind() {
	glDisableVertexAttribArray(Echeyde::TEXTURE); 
	glDisableVertexAttribArray(Echeyde::TANGENT);
	glDisableVertexAttribArray(Echeyde::NORMAL);
	glDisableVertexAttribArray(Echeyde::COLOR);
	glDisableVertexAttribArray(Echeyde::VERTEX);

}



void Mesh::display(glm::mat4 &projection, glm::mat4 &model, glm::mat4 &view) {

	if (displayed) {
		material.Bind(); 
		glUniformMatrix4fv(glGetUniformLocation(material.getProgram(), M_PROJECTION.c_str()), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(material.getProgram(), M_VIEW.c_str()), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(material.getProgram(), M_MODEL.c_str()), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(vao); 

		glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_SHORT, 0);

		glBindVertexArray(0); 

		Unbind();
		
		material.Unbind(); 

	}
}


