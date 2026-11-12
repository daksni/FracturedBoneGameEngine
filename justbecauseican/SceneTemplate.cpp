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


bool SceneTemplate::getSaveData(Save* save, Player* player) {

	if (save->load("data") == true) {
		//Apply necessary changes.
		if (save->saveData.sceneID == SCENE_ID) {
			player->setPlayerLife(save->saveData.playerLife);
			//player->setPlayerClass(save->saveData.playerClass);
			//player->setPlayerName(save->saveData.playerName);
			//player->setPlayerGender(save->saveData.playerGender);
		}
		return true;
	}
	else {
		std::cout << "\nFATAL ERROR: THE SAVE FILE DOES NOT EXIST.";
		return false;
	}

}

void SceneTemplate::playScene(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	if (getSaveData(save, player) == false) {
		return;
	}
	else {
		while (game->keepGameRunning == true) {
			//Add here the fucntions of the scene!
			//Usually you will want to generate a save only after a condition within the scene playthrough is met.
			//But having it seperate at the end of the exection should work.
			genNewSave(save, player);

			//game->stop(); // <-- This command will stop the game execution.

		}
	}
}

void SceneTemplate::genNewSave(Save* save, Player* player) {

	//Set the value of the saved information.
	save->saveData.sceneID = SCENE_ID + 1;
	save->saveData.playerLife = player->getPlayerLife();
	//save->saveData.playerClass = player->getPlayerClass();
	//save->saveData.playerName = player->getPlayerName();
	//save->saveData.playerGender = player->getPlayerGender();

	save->save("data");
}

int const SceneTemplate::getSceneID() {
	return SCENE_ID;
}