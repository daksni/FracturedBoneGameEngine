//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is a scene implementation example. Copy this for any new scene, or the SceneTemplate files.
//It is imperatve that any new save data made, be stored in all new scene headers.
//Ideally, you will copy every new scene, and only change what is saved and what is pulled. As well as what happens in the scene.

#include "Scene1.h"


bool Scene1::getSaveData(Player* player) {
	Scene1::SaveData saveData;

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

void Scene1::playScene(Player* player, Pronouns* pronouns, Game* game) {
	if (getSaveData(player) == false) {
		return;
	}
	else {

		//Add here the fucntions of the scene! Here a simple example where the game shuts off.
		std::cout << "NOTHING HERE AS WELL! THE GAME WILL CLOSE SOON!";

		//Usually you will want to generate a save after a condition is met.
		genNewSave(player);

		game->delay(5);
		game->keepGameRunning = false;
		

	}
}

void Scene1::genNewSave(Player* player) {
	Scene1::SaveData saveData;

	//Set the value of the saved information.
	saveData.sceneid = SCENE_ID + 1; //The save will change this to an invalid ID, and the game will reset.
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

int const Scene1::getSceneID() {
	return SCENE_ID;
}