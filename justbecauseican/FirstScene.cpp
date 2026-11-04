//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is the FirstScene, configure in here what is the first thing that happens in the game.

#include "FirstScene.h"

void FirstScene::playScene(Player* player, Pronouns* pronouns) {

		//Add here the fucntions of the scene!

		genNewSave(player);

	}
}

void FirstScene::genNewSave(Player* player) {
	FirstScene::SaveData saveData;

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

int FirstScene::getSceneID() {
	return SCENE_ID;
}