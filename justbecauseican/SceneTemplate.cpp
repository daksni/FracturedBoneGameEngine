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

void SceneTemplate::playScene(Game* game, Player* player, Pronouns* pronouns) {
	if (getSaveData(player) == false) {
		return;
	}
	else {
		while (game->keepGameRunning == true) {
			//Add here the fucntions of the scene!
			//Usually you will want to generate a save only after a condition within the scene playthrough is met.
			//But having it seperate at the end of the exection should work.
			genNewSave(player);

			//game->stop(); // <-- This command will stop the game execution.

		}
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

int const SceneTemplate::getSceneID() {
	return SCENE_ID;
}