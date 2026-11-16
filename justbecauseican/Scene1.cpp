//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is a scene implementation example. Copy this for any new scene, or the SceneTemplate files.
//It is imperatve that any new save data made, be stored in all new scene headers.
//Ideally, you will copy every new scene, and only change what is saved and what is pulled. As well as what happens in the scene.

#include "Scene1.h"
#include "GameObject.h"
#include "Mesh.h"
#include "CubeMeshPrimitive.h"
#include "PlaneMeshPrimitive.h"

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
	CubeMeshPrimitive cubeMesh;
	cubeMesh.createMesh();

	PlaneMeshPrimitive planeMesh;
	planeMesh.createMesh();
	
	GameObject cube;
	cube.setMesh(&cubeMesh);

	GameObject deadCube;
	deadCube.setMesh(&cubeMesh);

	GameObject plane;
	plane.setMesh(&planeMesh);

	float movementSpeed = 5.0f;

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
			//Clear the screen for ever new frame.
			game->clearScreen();

			game->setTicks();

			//Gets the FPS.
			game->getFPS();

			//Activate DEPTH TEST for proper vertex calculations.
			glEnable(GL_DEPTH_TEST);

			glUseProgram(shaders->cubeShaderProgram);

			glUniformMatrix4fv(shaders->cubeViewLocation, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(shaders->cubeProjectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

			cube.addGameObject(shaders->cubeShaderProgram, shaders->cubeModelLocation);
			cube.setColor(0.0f, 0.0f, 1.0f, 1.0f);


			deadCube.addGameObject(shaders->cubeShaderProgram, shaders->cubeModelLocation);
			deadCube.position.x = 3.0f;
			deadCube.position.y = 0.0f;
			deadCube.position.z = -10.0f;
			deadCube.setColor(1.0f, 0.0f, 0.0f, 1.0f);

			plane.addGameObject(shaders->cubeShaderProgram, shaders->cubeModelLocation);
			plane.position.x = 0.0f;
			plane.position.y = -1.0f;
			plane.position.z = -10.0f;
			plane.scale = glm::vec3(100.0f, 100.0f, 100.0f);
			plane.setColor(0.0f, 1.0f, 0.0f, 0.5f);


			//Disable depth test for text texture streaming.
			glDisable(GL_DEPTH_TEST);

			//Write texts in the screen.
			game->writeText("ARIAL", 40, "FPS: " + std::to_string(game->currentFPS), 1, 1, {255, 255, 255, 255});
			glUseProgram(shaders->textShaderProgram);

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
				cube.position.z -= movementSpeed * game->deltaTime;

			if (keyboardState[SDL_SCANCODE_S])
				cube.position.z += movementSpeed * game->deltaTime;

			if (keyboardState[SDL_SCANCODE_A])
				cube.position.x -= movementSpeed * game->deltaTime;

			if (keyboardState[SDL_SCANCODE_D])
				cube.position.x += movementSpeed * game->deltaTime;
            
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