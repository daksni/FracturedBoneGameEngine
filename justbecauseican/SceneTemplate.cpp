//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

#include "SceneTemplate.h"

//Declare any information that must be saved here. And in "SceneTemplate.h"
struct SceneManager::SaveData {
	int sceneid;
	int playerlife;
	std::string playername;
	int playergender;
	int playerclass;
};


//If you want to make this the first scene, and generate a save file,
//Change "IS_FIRST_SCENE" to "true" in "SceneTemplate.h" otherwise, this
//function will always attempt to load a previous save that may be nonexistent.
void SceneManager::getSaveData() {
	if (IS_FIRST_SCENE == true) {
		std::ofstream saveFile("data.fbgesvdt");
	}
	else if (IS_FIRST_SCENE == false) {
		std::ifstream saveFile("data.fbgesvdt");

		if (saveFile.is_open()) {

		}
	}
}

void SceneManager::playScene(Player* player, Pronouns* pronouns) {
	getSaveData();
	
	//Add here the fucntions of the scene!

	genNewSave(player);
}

void SceneManager::genNewSave(Player* player) {	
	SceneManager::SaveData saveData;
	
	//Set the value of the saved information.
	saveData.sceneid = SCENE_ID;
	saveData.playerlife = player->getPlayerLife();
	saveData.playerclass = player->getPlayerClass();
	saveData.playername = player->getPlayerName();
	saveData.playergender = player->getPlayerGender();

	//TODO: save file logic.
}