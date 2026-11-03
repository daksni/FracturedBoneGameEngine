//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

#include "SceneTemplate.h"

void SceneManager::getSaveData() {
	if (isFirstScene == true) {
		//TODO: make new save file
	}
	else if (isFirstScene == false) {
		//TODO: read save data
	}
}

void SceneManager::playScene(Player* player, Pronouns* pronouns) {
	//Add code here to define what happens in the game!
}

void SceneManager::genNewSave(Player* player) {

	//Add any relevant information here.
	struct SaveData{
		int playerlife;
		std::string playername;
		int playergender;
		int playerclass;
	};

	SaveData saveData;
	
	//Set the value of the saved information.
	saveData.playerlife = player->getPlayerLife();
	saveData.playerclass = player->getPlayerClass();
	saveData.playername = player->getPlayerName();
	saveData.playergender = player->getPlayerGender();

	//TODO: save file logic.
}