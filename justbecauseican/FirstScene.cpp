//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is the FirstScene, configure in here what is the first thing that happens in the game.

#include "FirstScene.h"


void FirstScene::playScene(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	bool isSceneOver = false;
	bool quitGame = false;

	game->clearScreen();
	game->writeText("ARIAL", 25, "WELCOME TO THE SIM.!", 1, 1, { 255, 255, 255, 255 });
	game->writeText("ARIAL", 25, "Press[1] to START. Press[2] to QUIT the game.", 1, 30, { 255, 255, 255, 255 });
	game->render();

	while (isSceneOver == false) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			while (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_1) {
					isSceneOver = true;
					break;
				}
				else if (event.key.key == SDLK_2) {
					isSceneOver = true;
					quitGame = true;
					break;
				}
			}
		}
	}

	if (isSceneOver == true && quitGame == false) {
		genNewSave(save, player);
	}
	else if (quitGame == true) {
		game->stop();
	}


}

	void FirstScene::genNewSave(Save* save, Player * player) {
		//Set the value of the saved information.
		save->saveData.sceneID = SCENE_ID + 1;
		save->saveData.playerLife = player->getPlayerLife();
		//save->saveData.playerClass = player->getPlayerClass();
		//save->saveData.playerName = player->getPlayerName();
		//save->saveData.playerGender = player->getPlayerGender();

		save->save("data");
	}


	int const FirstScene::getSceneID() {
		return SCENE_ID;
	}