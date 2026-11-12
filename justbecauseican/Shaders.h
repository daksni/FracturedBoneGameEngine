#pragma once
#include "All.h"
class Shaders
{
public:
	GLuint textVAO = 0;
	GLuint textVBO = 0;
	GLuint textShaderProgram = 0;

	GLuint cubeVBO = 0;
	GLuint cubeVAO = 0;
	GLuint cubeEBO = 0;
	GLuint cubeShaderProgram = 0;
	GLint cubeModelLocation = -1;
	GLint cubeViewLocation = -1;
	GLint cubeProjectionLocation = -1;

	std::string loadShader(const std::string& filePath);

	void initTextShaders();
	void init3DCubePrimitiveShaders();
	~Shaders();
};

