//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <fstream>

#include "Player.h"
#include "Pronouns.h"

class Game
{
public:

	void delay(int delayTime);
	bool keepGameRunning = true;

	int loadGame();

	void settingHowThePlayerShouldBeCalled(Player* player);
	void settingThePlayerGender(Player* player);
	void settingThePlayerClass(Player* player, Pronouns* pronouns);

	void setup(Game* game, Player* player, Pronouns* pronouns);
	void sceneScheduler(Game* game, Player* player, Pronouns* pronouns);
	void loadSceneFromSaveGame(Game* game, Player* player, Pronouns* pronouns);

	void run(Game* game, Player* player, Pronouns* pronouns);
	

};

