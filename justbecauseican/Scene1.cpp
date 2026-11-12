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


void Scene1::playScene(Game* game, Shaders* shaders, Save* save, Player* player, Pronouns* pronouns) {
	//Define variables for cube movement.
	glm::vec3 cubePosition(0.0f, 0.0f, 0.0f);
	float movementSpeed = 5.0f;
	Uint64 previousTicks = SDL_GetTicks();

	// Camera position in world space.
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);

	// Where the camera is looking.
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

	// Which direction is up.
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// View matrix: positions and orients the camera.
	glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	int screenWidth;
	int screenHeight;

	SDL_GetWindowSizeInPixels(game->window, &screenWidth, &screenHeight);

	float aspectRatio = (float)screenWidth / (float)screenHeight;

	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		aspectRatio,
		0.1f,
		100.0f
	);

	glViewport(0, 0, screenWidth, screenHeight);

    if (getSaveData(save, player) == false) {
        return;
    }
    else {
        while (game->keepGameRunning == true) {
			// Calculate delta time.
			Uint64 currentTicks = SDL_GetTicks();
			float deltaTime = (currentTicks - previousTicks) / 1000.0f;
			previousTicks = currentTicks;

			//Clear the screen for ever new frame.
			game->clearScreen();

			//Write texts in the screen.
			game->writeText("ARIAL", 25, "A CUBE!", 1, 1, { 255, 255, 255, 255 });
			glUseProgram(shaders->textShaderProgram);

			//Activate DEPTH TEST for proper vertex calculations.
			glEnable(GL_DEPTH_TEST);

			//Make the model matrix.
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePosition);

			//Use the cube shading program.
			glUseProgram(shaders->cubeShaderProgram);

			//Assing transformation and perspective matrices.
			glUniformMatrix4fv(shaders->cubeModelLocation, 1, GL_FALSE, glm::value_ptr(model));
			glUniformMatrix4fv(shaders->cubeViewLocation, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(shaders->cubeProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

			//Bind the vertex array for the Cube Vertex Array Object.
			glBindVertexArray(shaders->cubeVAO);

			//Draw elements to the screen.
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			//RENDER EVERYTHING.
			game->render();

			//Quit the game on ESCAPE.
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EVENT_KEY_DOWN) {
					if (event.key.key == SDLK_ESCAPE) {
						game->stop();
					}
				}
			}

			// Read keyboard state.
			const bool* keyboardState = SDL_GetKeyboardState(nullptr);

			// Movement.
			if (keyboardState[SDL_SCANCODE_W])
				cubePosition.z -= movementSpeed * deltaTime;

			if (keyboardState[SDL_SCANCODE_S])
				cubePosition.z += movementSpeed * deltaTime;

			if (keyboardState[SDL_SCANCODE_A])
				cubePosition.x -= movementSpeed * deltaTime;

			if (keyboardState[SDL_SCANCODE_D])
				cubePosition.x += movementSpeed * deltaTime;
            
        }
    }
}


void Scene1::genNewSave(Save* save, Player* player) {

	//Set the value of the saved information.
	save->saveData.sceneID = SCENE_ID + 1;
	save->saveData.playerLife = player->getPlayerLife();
	//save->saveData.playerClass = player->getPlayerClass();
	//save->saveData.playerName = player->getPlayerName();
	//save->saveData.playerGender = player->getPlayerGender();

	save->save("data");
}

int const Scene1::getSceneID() {
	return SCENE_ID;
}