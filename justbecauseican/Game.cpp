//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Game.h"

//Import every scene here:
#include "FirstScene.h"
#include "Scene1.h"

//================================ SCENE DECLARATIONS =================================//
//Create an instance of every scene here:
FirstScene firstScene;
Scene1 scene1;

//================================= AUXILIARY FUNCTIONS ===================================//

void Game::delay(int delayTime) {
	std::this_thread::sleep_for(std::chrono::seconds(delayTime));
}

void Game::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::render() {
	SDL_GL_SwapWindow(window);
}

void Game::initAllShaders() {
	shaders->initTextShaders();
	shaders->init3DCubePrimitiveShaders();
}

//=============================================== TEXT CREATION =================================================//

int Game::writeText(std::string fontName, int fontSize, std::string text, float x_coord, float y_coord, SDL_Color color) {
	// Locate and configure the font.
	std::string fontPath = fontName + ".ttf";

	font = TTF_OpenFont(
		fontPath.c_str(),
		fontSize
	);

	if (font == nullptr) {
		SDL_Log("Font loading failed: %s", SDL_GetError());
		return -1;
	}

	// Render text into an SDL surface.
	SDL_Surface* textSurface = TTF_RenderText_Blended(
		font,
		text.c_str(),
		0,
		color
	);

	if (textSurface == nullptr) {
		TTF_CloseFont(font);
		return -1;
	}

	// Convert surface to a predictable RGBA pixel format.
	SDL_Surface* convertedSurface = SDL_ConvertSurface(
		textSurface,
		SDL_PIXELFORMAT_RGBA32
	);

	SDL_DestroySurface(textSurface);

	if (convertedSurface == nullptr) {
		TTF_CloseFont(font);
		return -1;
	}

	// Generate an OpenGL texture.
	GLuint textTexture = 0;
	glGenTextures(1, &textTexture);
	glBindTexture(GL_TEXTURE_2D, textTexture);

	// Configure texture filtering and wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Upload surface pixels to the GPU.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, convertedSurface->pitch / 4);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		convertedSurface->w,
		convertedSurface->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		convertedSurface->pixels
	);

	// Restore pixel unpack settings.
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	// Prepare the text rectangle.
	float width = (float)convertedSurface->w;
	float height = (float)convertedSurface->h;

	float vertices[] = {
		// Position             // Texture coordinates
		x_coord,         y_coord,          0.0f, 0.0f,
		x_coord + width, y_coord,          1.0f, 0.0f,
		x_coord + width, y_coord + height, 1.0f, 1.0f,

		x_coord,         y_coord,          0.0f, 0.0f,
		x_coord + width, y_coord + height, 1.0f, 1.0f,
		x_coord,         y_coord + height, 0.0f, 1.0f
	};

	// Activate the text shader.
	glUseProgram(shaders->textShaderProgram);

	// Supply screen dimensions to the shader.
	int screenWidth = 0;
	int screenHeight = 0;

	SDL_GetWindowSizeInPixels(window, &screenWidth, &screenHeight);

	GLint screenSizeLocation = glGetUniformLocation(
		shaders->textShaderProgram,
		"screenSize"
	);

	glUniform2f(
		screenSizeLocation,
		(float)screenWidth,
		(float)screenHeight
	);

	// Activate texture unit 0.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textTexture);

	GLint textSamplerLocation = glGetUniformLocation(
		shaders->textShaderProgram,
		"textTexture"
	);

	glUniform1i(textSamplerLocation, 0);

	// Upload updated rectangle geometry.
	glBindVertexArray(shaders->textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, shaders->textVBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_DYNAMIC_DRAW
	);

	// Enable transparency.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the text.
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Release temporary resources.
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDeleteTextures(1, &textTexture);

	SDL_DestroySurface(convertedSurface);
	TTF_CloseFont(font);

	return 0;
}

//============================ CHECK FOR SAVE FILE =======================================//

int Game::loadGame(Save* save) {
	int fetchID;
	if(save->load("data")){
	fetchID = save->saveData.sceneID;
	return fetchID;
	}
	else {
		return 0;
	}
}

//======================================== CREATE WINDOW ==================================//

int Game::makeWindow() {

	// Initialize SDL.
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL initialization failed: %s", SDL_GetError());
		return -1;
	}

	// Request OpenGL 4.6 Core.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	// Create the OpenGL window.
	window = SDL_CreateWindow(
		"Elder Bone Software -- Fractured Bone Game Engine",
		1920,
		1080,
		SDL_WINDOW_OPENGL
	);

	if (window == nullptr) {
		SDL_Log("Window creation failed: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	// Create OpenGL context.
	context = SDL_GL_CreateContext(window);

	if (context == nullptr) {
		SDL_Log("OpenGL context creation failed: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Initialize GLAD.
	if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
		SDL_Log("GLAD initialization failed!");
		SDL_GL_DestroyContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	// Initialize SDL_ttf.
	if (!TTF_Init()) {
		SDL_Log("TTF initialization failed: %s", SDL_GetError());
		return -1;
	}

	return 0;
}

//========================================= GAME CORE =====================================//

//Schedules All scenes. ADD EVERY SCENE HERE IN ORDER!
void Game::sceneScheduler(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	while (keepGameRunning == true) {
		firstScene.playScene(game, save, player, pronouns);
		scene1.playScene(game, shaders, save, player, pronouns);
	}
	
}

//Checks if there's a previous save and load based on the sceneID.
void Game::loadSceneFromSaveGame(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	//Fetch the scene ID of a previous save if there is one:
	int sceneID = loadGame(save);

	//Check the scene IDs to load proper scene.
	//ALL SCENES MUST BE HERE FOR A PROPER LOAD. Add "else if"s for new IDs.
	if (sceneID != 0) { 
		if (sceneID == scene1.getSceneID()) {
			scene1.playScene(game, shaders, save, player, pronouns);
		}
		else {
			//If none of the possible IDs match a scene, reload the setup.
			sceneScheduler(game, save, player, pronouns);
		}

	}
	else { //If there is no previous save, load the setup.
		sceneScheduler(game, save, player, pronouns);
	}
}

void Game::run(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	makeWindow();
	initAllShaders();
	loadSceneFromSaveGame(game, save, player, pronouns);
}

//THIS COMMAND KILLS THE GAME. ONLY USE IT IF THAT IS THE DESIRED FUNCTION.
void Game::stop() {

	delete shaders;
	shaders = nullptr;

	TTF_Quit();

	
	SDL_GL_DestroyContext(context);
	context = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();

	keepGameRunning = false;
}