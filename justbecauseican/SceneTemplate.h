//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

//If you already have other scenes in your game, it is recommended that you copy them for use.
//This engine already has a FirstScene and Scene1 as working examples to structure your game frome there.
//However, if for whatever reason, you want the empty code without implementation...
//this is the basic functionality of the scene code.

#pragma once
#include "Game.h"

class SceneTemplate //Every new scene MUST HAVE a different CLASS NAME!
					//Otherwise the code will confilct with other instances of "SceneTemplate."
					//Check the FirstScene, and Scene1 implementation for reference.
{
private:
	const int SCENE_ID = 1; //Change the ID for each scene sequentially.
public:

	bool getSaveData(Save* save, Player* player); //Scan the system for previous saves before loading new scene.
	void playScene(Game* game, Save* save, Player* player, Pronouns* pronouns); //Load a new scene
	void genNewSave(Save* save, Player* player); //Save any relevant information.

	int const getSceneID();
};

