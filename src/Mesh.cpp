/*
The Mesh class
A grid represents a single, drawable entity.
It contains a set of points (vertex coordinates, normal vectors, corresponding map coordinates), map sets, indices (for EBO)
The data of the graphable entity is to be written to VAO, VBO, EBO

When initializing the mesh, configure the VAO, VBO, and EBO to be used and write data into them in the desired format
Encapsulates the Draw function, which binds all texture maps and sends them to shader through uniform, binds VAO at the same time, and starts drawing graphs (triangles) using the data that has been written in VAO, VBO and EBO before.
*/

#include "Mesh.h"

Mesh::Mesh(float vertices[]) {
	this->vertices.resize(36);
	memcpy(&this->vertices[0], vertices, sizeof(float) * 8 * 36);

	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<unsigned int> _indices, std::vector<Texture> _textures) {
	this->vertices = _vertices;
	this->indices = _indices;
	this->textures = _textures;
	
	setupMesh();
}

Mesh::~Mesh() {}

void Mesh::Draw(Shader *shader) {
	for (unsigned int i = 0; i < textures.size(); i++) {
		if (textures[i].type == "texture_diffuse") {
			glActiveTexture(GL_TEXTURE0);					//Activate slot 0
			glBindTexture(GL_TEXTURE_2D, textures[i].id);	//Bind the texture corresponding to the id to the active slot
			shader->SetUniform1i("material.diffuse", 0);	//Corresponds to the shader
		}
		else if (textures[i].type == "texture_specular") {
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->SetUniform1i("material.specular", 1);
		}
	}
	glBindVertexArray(VAO);		//Bind VAO

//	glDrawArrays(GL_TRIANGLES, 0, 36);	//to be replaced
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);	//Drawing graphics, parameters: drawing graphics, size, type, offset
	
	glBindVertexArray(0);		//untie
	glActiveTexture(GL_TEXTURE0);	//Return the texture slot to bit 0
}

void Mesh::setupMesh() {
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// to be continue
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));

}
