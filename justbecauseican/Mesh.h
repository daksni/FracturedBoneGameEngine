#pragma once
#include "All.h"

class Mesh
{
public:
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint EBO = 0;
    GLsizei indexCount = 0;

    virtual void createMesh() = 0;

    void uploadMesh(const float* vertices, size_t vertexSize, const GLuint* indices, size_t indexSize, GLsizei indicesCount);

	void addMesh();

	virtual ~Mesh();

};

