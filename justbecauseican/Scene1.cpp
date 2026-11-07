//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is a scene implementation example. Copy this for any new scene, or the SceneTemplate files.
//It is imperatve that any new save data made, be stored in all new scene headers.
//Ideally, you will copy every new scene, and only change what is saved and what is pulled. As well as what happens in the scene.

#include "Scene1.h"


bool Scene1::getSaveData(Save* save, Player* player) {

	if (save->load("data") == true) {
		//Apply necessary changes.
		if (save->saveData.sceneID == SCENE_ID) {
			player->setPlayerLife(save->saveData.playerLife);
			player->setPlayerClass(save->saveData.playerClass);
			player->setPlayerName(save->saveData.playerName);
			player->setPlayerGender(save->saveData.playerGender);
		}
		return true;
	}
	else {
		std::cout << "\nFATAL ERROR: THE SAVE FILE DOES NOT EXIST.";
		return false;
	}

}

void Scene1::playScene(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	if (getSaveData(save, player) == false) {
		return;
	}
	else {
		while (game->keepGameRunning == true) {

			//Add here the fucntions of the scene! Here a simple example where the game shuts off.
			game->clearScreen();
			game->writeText("ARIAL", 25, "NOTHING IN THE MOMENT. THE GAME WILL QUIT SHORTLY", 1, 1, { 255, 255, 255, 255 });
			game->render();

			//Usually you will want to generate a save after a condition is met.
			genNewSave(save, player);

			game->delay(2);
			game->stop();

		}
	}
}

void Scene1::genNewSave(Save* save, Player* player) {

	//Set the value of the saved information.
	save->saveData.sceneID = SCENE_ID + 1; //The save will change this to an invalid ID, and the game will reset.
	save->saveData.playerLife = player->getPlayerLife();
	save->saveData.playerClass = player->getPlayerClass();
	save->saveData.playerName = player->getPlayerName();
	save->saveData.playerGender = player->getPlayerGender();

	save->save("data");
}

int const Scene1::getSceneID() {
	return SCENE_ID;
}