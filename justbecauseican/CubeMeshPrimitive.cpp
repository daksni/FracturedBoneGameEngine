#include "CubeMeshPrimitive.h"
#include "Shaders.h"

void CubeMeshPrimitive::createMesh() {
	//Rendering information.


	float vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		// Front face
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f
	};

	GLuint indices[] = {
		// Back face
		0, 1, 2,
		2, 3, 0,

		// Front face
		4, 5, 6,
		6, 7, 4,

		// Left face
		0, 3, 7,
		7, 4, 0,

		// Right face
		1, 5, 6,
		6, 2, 1,

		// Bottom face
		0, 4, 5,
		5, 1, 0,

		// Top face
		3, 2, 6,
		6, 7, 3
	};

	uploadMesh(
		vertices,
		sizeof(vertices),
		indices,
		sizeof(indices),
		36
	);

}
