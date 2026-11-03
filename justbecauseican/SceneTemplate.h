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
	const bool IS_FIRST_SCENE = false; //If this is in fact the first scene, change to "true".
	const int SCENE_ID = 1; //Change the ID for each scene sequentially. If this is the first scene, change it to "0".
public:
	//Declare any information that must be saved here. And in "SceneTemplate.cpp"
	struct SaveData{int sceneid; int playerlife; std::string playername; int playergender; int playerclass;};


	void getSaveData(); //Scan the system for previous saves before loading new scene.
	void playScene(Player* player, Pronouns* pronouns); //Load a new scene
	void genNewSave(Player* player); //Save any relevant information.
};

