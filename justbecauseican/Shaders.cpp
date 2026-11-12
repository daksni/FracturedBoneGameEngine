#include "Shaders.h"

//============================= LOAD SHADER =========================================//
std::string Shaders::loadShader(const std::string& filePath)
{
	std::ifstream file(filePath);
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
	std::string textVertexCode = loadShader("text_vertex.glsl");
	std::string textFragmentCode = loadShader("text_fragment.glsl");

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

void Shaders::init3DCubePrimitiveShaders() {
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

	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);

	// Bind VAO 
	glBindVertexArray(cubeVAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

	// Upload vertex data
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
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
	glGenBuffers(1, &cubeEBO);

	glBindVertexArray(cubeVAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW
	);


	glEnableVertexAttribArray(0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//Create Shaders
	std::string vertexCode = loadShader("cube_vertex.glsl");
	std::string fragmentCode = loadShader("cube_fragment.glsl");


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
	cubeShaderProgram = glCreateProgram();

	glAttachShader(cubeShaderProgram, vertexShader);
	glAttachShader(cubeShaderProgram, fragmentShader);
	glLinkProgram(cubeShaderProgram);

	cubeModelLocation = glGetUniformLocation(cubeShaderProgram, "model");
	cubeViewLocation = glGetUniformLocation(cubeShaderProgram, "view");
	cubeProjectionLocation = glGetUniformLocation(cubeShaderProgram, "projection");

	//Delete the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shaders::~Shaders() {

	glDeleteVertexArrays(1, &textVAO);
	glDeleteBuffers(1, &textVBO);
	glDeleteProgram(textShaderProgram);

	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
	glDeleteBuffers(1, &cubeEBO);
	glDeleteProgram(cubeShaderProgram);

}