//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "Game.h"

class Scene1
{
private:
	const int SCENE_ID = 2; //Change the ID for each scene sequentially.
public:
	
	bool getSaveData(Save* save, Player* player); //Scan the system for previous saves before loading new scene.
	void playScene(Game* game, Save* save, Player* player, Pronouns* pronouns); //Load a new scene
	void genNewSave(Save* save, Player* player); //Save any relevant information.

	int const getSceneID();

};

