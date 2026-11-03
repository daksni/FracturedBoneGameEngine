//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

#pragma once

#include "Game.h"

class SceneManager
{
private:
	struct saveData{};
public:

	void getSaveData(); //Scan the system for previous saves before loading new scene.
	void playScene(Player* player, Pronouns* pronouns); //Load a new scene
	int genNewSave(); //Save any relevant information.
};

