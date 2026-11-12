//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "All.h"
#include "Player.h"
#include "Pronouns.h"
#include "Save.h"
#include "Shaders.h"

class Game
{
public:
	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;
	TTF_Font* font = nullptr;

	Shaders* shaders = new Shaders();

	void delay(int delayTime);
	bool keepGameRunning = true;

	int loadGame(Save* save);

	void sceneScheduler(Game* game, Save* save, Player* player, Pronouns* pronouns);
	void loadSceneFromSaveGame(Game* game, Save* save, Player* player, Pronouns* pronouns);

	int writeText(std::string fontName, int fontSize, std::string text, float x_coord, float y_coord, SDL_Color color);

	void render();
	void clearScreen();
	void initAllShaders();
	int makeWindow();

	std::string loadShader(const std::string& filePath);

	void run(Game* game, Save* save, Player* player, Pronouns* pronouns);
	void stop();
	

};

