//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

#pragma once
#include "Game.h"

class FirstScene
{
private:
	const int SCENE_ID = 1;
public:
	
	void playScene(Game* game, Save* save, Player* player, Pronouns* pronouns); 
	void genNewSave(Save* save, Player* player);

	int const getSceneID();

};

