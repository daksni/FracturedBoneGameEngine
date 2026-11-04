//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once
#include "Game.h"

class Scene1
{
private:
	const int SCENE_ID = 1; //Change the ID for each scene sequentially.
public:

	//Declare any information that must be saved here.
	struct SaveData{
	int sceneid;
	int playerlife;
	std::string playername;
	int playergender;
	int playerclass;};


	bool getSaveData(Player* player); //Scan the system for previous saves before loading new scene.
	void playScene(Player* player, Pronouns* pronouns); //Load a new scene
	void genNewSave(Player* player); //Save any relevant information.

	int getSceneID();
};

