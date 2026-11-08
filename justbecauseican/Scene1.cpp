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

    // Starter positions.
    int playerPosX = 400;
    int playerPosY = 300;

    int tagPosX = playerPosX;
    int tagPosY = playerPosY;

    bool moveUp = false;
    bool moveDown = false;
    bool moveRight = false;
    bool moveLeft = false;

    // World boundaries.
    int worldMinX = 20;
    int worldMaxX = 750;
    int worldMinY = 50;
    int worldMaxY = 550;

    if (getSaveData(save, player) == false) {
        return;
    }
    else {
        while (game->keepGameRunning == true) {

            SDL_Event event;

            while (SDL_PollEvent(&event)) {

                if (event.type == SDL_EVENT_QUIT) {
                    genNewSave(save, player);
                    game->stop();
                }

                if (event.type == SDL_EVENT_KEY_DOWN) {

                    //Process movement in.
                    if (event.key.key == SDLK_W) moveUp = true;
                    if (event.key.key == SDLK_S) moveDown = true;
                    if (event.key.key == SDLK_D) moveRight = true;
                    if (event.key.key == SDLK_A) moveLeft = true;

                    //Quit on ESC.
                    if (event.key.key == SDLK_ESCAPE) {
                        genNewSave(save, player);
                        game->stop();
                    }

                }

                else if (event.type == SDL_EVENT_KEY_UP) {

                    //Process movement out
                    if (event.key.key == SDLK_W) moveUp = false;
                    if (event.key.key == SDLK_S) moveDown = false;
                    if (event.key.key == SDLK_D) moveRight = false;
                    if (event.key.key == SDLK_A) moveLeft = false;

                }
               
            }

            // Calculate intended movement.
            int nextX = playerPosX;
            int nextY = playerPosY;

            if (moveUp) nextY -= 1;
            if (moveDown) nextY += 1;
            if (moveRight) nextX += 1;
            if (moveLeft) nextX -= 1;

            // Check world boundaries.
            if (nextX >= worldMinX && nextX <= worldMaxX &&
                nextY >= worldMinY && nextY <= worldMaxY) {

                playerPosX = nextX;
                playerPosY = nextY;

            }

            // Update name tag position.
            tagPosX = playerPosX - 2;
            tagPosY = playerPosY + 30;

            game->clearScreen();

            // Draw Player's sprite accordingly to class.
            if (player->getPlayerClass() == Player::PlayerClass::KNIGHT) {
                game->writeText("ARIAL", 25, "+[]+", playerPosX, playerPosY, { 200, 200, 200, 255 });
            }
            else if (player->getPlayerClass() == Player::PlayerClass::WIZARD) {
                game->writeText("ARIAL", 25, "![]!", playerPosX, playerPosY, { 200, 255, 255, 255 });
            }
            else if (player->getPlayerClass() == Player::PlayerClass::BARD) {
                game->writeText("ARIAL", 25, "[^]{", playerPosX, playerPosY, { 255, 255, 200, 255 });
            }
            else if (player->getPlayerClass() == Player::PlayerClass::NOBLE) {
                game->writeText("ARIAL", 25, "^{~}^", playerPosX, playerPosY, { 255, 200, 200, 255 });
            }
            else if (player->getPlayerClass() == Player::PlayerClass::WRETCH) {
                game->writeText("ARIAL", 25, "[]", playerPosX, playerPosY, { 200, 255, 200, 255 });
            }

            // Draw Player's name tag, accordingly to gender.
            if (player->getPlayerGender() == Player::PlayerGender::MALE) {
                game->writeText("ARIAL", 11, player->getPlayerName(), tagPosX, tagPosY, { 100, 255, 255, 255 });
            }
            else if (player->getPlayerGender() == Player::PlayerGender::FEMALE) {
                game->writeText("ARIAL", 11, player->getPlayerName(), tagPosX, tagPosY, { 255, 180, 255, 255 });
            }

            game->render();

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