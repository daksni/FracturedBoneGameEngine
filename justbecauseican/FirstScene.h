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

	//Declare any information that must be saved here.
	struct SaveData {
		int sceneid;
		int playerlife;
		std::string playername;
		int playergender;
		int playerclass;
	};

	
	void playScene(Game* game, Player* player, Pronouns* pronouns); 
	void genNewSave(Player* player);

	int const getSceneID();

};

