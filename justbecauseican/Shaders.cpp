#include "Shaders.h"

//============================= LOAD SHADER =========================================//
std::string Shaders::loadShader(const std::string& filePath)
{
	std::ifstream file("shaders\\" + filePath + ".glsl");
	std::stringstream buffer;

	buffer << file.rdbuf();

	return buffer.str();
}

//==================================== MAKE AND COMPILE SHADERS ====================================//

//TEXT SHADER.
void Shaders::initTextShaders() {
	// Create VAO and VBO.

	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);

	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(float) * 24,
		nullptr,
		GL_DYNAMIC_DRAW
	);

	// Position attribute.
	glVertexAttribPointer(
		0, 2, GL_FLOAT, GL_FALSE,
		4 * sizeof(float), (void*)0
	);
	glEnableVertexAttribArray(0);

	// Texture coordinate attribute.
	glVertexAttribPointer(
		1, 2, GL_FLOAT, GL_FALSE,
		4 * sizeof(float),
		(void*)(2 * sizeof(float))
	);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Create texture shaders
	std::string textVertexCode = loadShader("text_vertex");
	std::string textFragmentCode = loadShader("text_fragment");

	//Make and compile text Vertex shader
	GLuint textVertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* textVertexSource = textVertexCode.c_str();
	glShaderSource(textVertexShader, 1, &textVertexSource, nullptr);
	glCompileShader(textVertexShader);

	//Make and compile text Fragment shader
	GLuint textFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* textFragmentSource = textFragmentCode.c_str();
	glShaderSource(textFragmentShader, 1, &textFragmentSource, nullptr);
	glCompileShader(textFragmentShader);

	//Make shader program
	textShaderProgram = glCreateProgram();

	glAttachShader(textShaderProgram, textVertexShader);
	glAttachShader(textShaderProgram, textFragmentShader);
	glLinkProgram(textShaderProgram);

	//Delete shaders.
	glDeleteShader(textVertexShader);
	glDeleteShader(textFragmentShader);

}

void Shaders::init3D_PrimitiveShaders() {

	//Create Shaders
	std::string vertexCode = loadShader("prim_mesh_vrtx");
	std::string fragmentCode = loadShader("prim_mesh_frag");


	//Make and compile Vertex Shader.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSource = vertexCode.c_str();
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);


	//Make and compile Fragment Shader.
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSource = fragmentCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);


	//Make Shader Program.
	meshShaderProgram = glCreateProgram();

	glAttachShader(meshShaderProgram, vertexShader);
	glAttachShader(meshShaderProgram, fragmentShader);
	glLinkProgram(meshShaderProgram);

	meshModelLocation = glGetUniformLocation(meshShaderProgram, "model");
	meshViewLocation = glGetUniformLocation(meshShaderProgram, "view");
	meshProjectionLocation = glGetUniformLocation(meshShaderProgram, "projection");

	//Delete the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shaders::~Shaders() {

	glDeleteVertexArrays(1, &textVAO);
	glDeleteBuffers(1, &textVBO);
	glDeleteProgram(textShaderProgram);

	glDeleteProgram(meshShaderProgram);

}