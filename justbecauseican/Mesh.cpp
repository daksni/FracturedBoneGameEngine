#include "Mesh.h"


void Mesh::addMesh() {
    
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
   
}

void Mesh::uploadMesh(const float* vertices, size_t vertexSize, const GLuint* indices, size_t indexSize, GLsizei indicesCount) {
	indexCount = indicesCount;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO 
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Upload vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		vertexSize,
		vertices,
		GL_STATIC_DRAW
	);

	// Describe vertex attributes
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*)0
	);

	//Create the EBO.
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		indexSize,
		indices,
		GL_STATIC_DRAW
	);


	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

Mesh::~Mesh()
{
    if (VAO != 0) glDeleteVertexArrays(1, &VAO);

    if (VBO != 0) glDeleteBuffers(1, &VBO);

    if (EBO != 0) glDeleteBuffers(1, &EBO);
}