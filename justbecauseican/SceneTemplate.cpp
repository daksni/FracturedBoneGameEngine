//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//THIS IS A SCENE TEMPLATE
//FOR GAME DEVELOPMENT PURPOSES, **DO NOT** CHANGE THIS FILE!
//MAKE A NEW COPY FOR EACH SCENE.

#include "SceneTemplate.h"


bool SceneTemplate::getSaveData(Player* player) {
	SceneTemplate::SaveData saveData;

	std::ifstream saveFile("data.fbgesvdt");

	if (saveFile.is_open()) {
		//Read the data.
		saveFile >> saveData.sceneid;
		saveFile >> saveData.playerlife;
		saveFile >> saveData.playerclass;
		std::getline(saveFile >> std::ws, saveData.playername);
		saveFile >> saveData.playergender;

		//Apply necessary changes.
		if (saveData.sceneid == SCENE_ID) {
			player->setPlayerLife(saveData.playerlife);
			player->setPlayerClass(saveData.playerclass);
			player->setPlayerName(saveData.playername);
			player->setPlayerGender(saveData.playergender);
			return true;
		}
		else {
			return false;
		}
		return false;
	}
}

void SceneTemplate::playScene(Player* player, Pronouns* pronouns) {
	if (getSaveData(player) == false) {
		//do something
	}
	else {

		//Add here the fucntions of the scene!
		std::cout << "\n\n\nYou have loaded the empty template scene! :D\nDown below we will dump the player attributes:";
		player->vomitAllAttr();
		std::cout << "\nIf you run the game again, this will be what you will see! In the future, add more scenes :D\n\n\n";

		genNewSave(player);

	}
}

void SceneTemplate::genNewSave(Player* player) {
	SceneTemplate::SaveData saveData;

	//Set the value of the saved information.
	saveData.sceneid = SCENE_ID + 1;
	saveData.playerlife = player->getPlayerLife();
	saveData.playerclass = player->getPlayerClass();
	saveData.playername = player->getPlayerName();
	saveData.playergender = player->getPlayerGender();

	//Save values to the save file.
	std::ofstream saveFile("data.fbgesvdt");
	saveFile << saveData.sceneid << "\n";
	saveFile << saveData.playerlife << "\n";
	saveFile << saveData.playerclass << "\n";
	saveFile << saveData.playername << "\n";
	saveFile << saveData.playergender << "\n";
}

int SceneTemplate::getSceneID() {
	return SCENE_ID;
}