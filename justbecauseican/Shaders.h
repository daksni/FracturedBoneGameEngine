#pragma once
#include "All.h"
class Shaders
{
public:
	GLuint textVAO = 0;
	GLuint textVBO = 0;
	GLuint textShaderProgram = 0;

	
	GLuint meshShaderProgram = 0;
	GLint meshModelLocation = -1;
	GLint meshViewLocation = -1;
	GLint meshProjectionLocation = -1;

	std::string loadShader(const std::string& filePath);

	void initTextShaders();
	void init3D_PrimitiveShaders();
	~Shaders();
};

