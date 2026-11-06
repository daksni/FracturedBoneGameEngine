//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Player.h"
#include "Pronouns.h"

class Game
{
public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;

	void delay(int delayTime);
	bool keepGameRunning = true;

	int loadGame();

	void settingHowThePlayerShouldBeCalled(Player* player);
	void settingThePlayerGender(Player* player);
	void settingThePlayerClass(Player* player, Pronouns* pronouns);

	void setup(Game* game, Player* player, Pronouns* pronouns);
	void sceneScheduler(Game* game, Player* player, Pronouns* pronouns);
	void loadSceneFromSaveGame(Game* game, Player* player, Pronouns* pronouns);

	int writeText(std::string fontName, int fontSize, std::string text, float x_coord, float y_coord, SDL_Color color);
	void render();

	void clearScreen();
	int makeWindow();

	void run(Game* game, Player* player, Pronouns* pronouns);
	void stop();
	

};

