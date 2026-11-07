//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Game.h"

//Import every scene here:
#include "FirstScene.h"
#include "Scene1.h"

//================================ SCENE DECLARATIONS =================================//
//Create an instance of every scene here:
FirstScene firstScene;
Scene1 scene1;

//================================= AUXILIARY FUNCTIONS ===================================//

void Game::delay(int delayTime) {
	std::this_thread::sleep_for(std::chrono::seconds(delayTime));
}


int Game::writeText(std::string fontName, int fontSize, std::string text, float x_coord, float y_coord, SDL_Color color) {
	//Locate and configure the font.
	std::string fontPath = fontName + ".ttf";

	font = TTF_OpenFont(
		fontPath.c_str(), //Targeted font
		fontSize //Font size
	);

	if (font == nullptr) {
		SDL_Log("Font loading failed: %s", SDL_GetError());
		return -1;
	}

	//Render the text into a surface.
	SDL_Surface* textSurface = TTF_RenderText_Blended(
		font,
		text.c_str(),
		0,
		color
	);

	if (textSurface == nullptr) {
		TTF_CloseFont(font);
		return -1;
	}

	//Convert the surface into a texture.
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(
		renderer,
		textSurface
	);

	if (textTexture == nullptr) {
		SDL_DestroySurface(textSurface);
		TTF_CloseFont(font);
		return -1;
	}

	//Define the text position.
	SDL_FRect textPosition = {
		x_coord,
		y_coord,
		(float)textSurface->w,
		(float)textSurface->h
	};

	//Draw the text.
	SDL_RenderTexture(renderer, textTexture, nullptr, &textPosition);

	//Release temporary resources.
	SDL_DestroyTexture(textTexture);
	SDL_DestroySurface(textSurface);
	TTF_CloseFont(font);


	return 0;
}

void Game::clearScreen() {
	SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);

	SDL_RenderClear(renderer);
}

void Game::render() {
	SDL_RenderPresent(renderer);
}

//============================ CHECK FOR SAVE FILE =======================================//

int Game::loadGame(Save* save) {
	int fetchID;
	if(save->load("data")){
	fetchID = save->saveData.sceneID;
	return fetchID;
	}
	else {
		return 0;
	}
}

//======================================== CREATE WINDOW ==================================//

int Game::makeWindow() {
		//Initialize the window.
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return -1;
	}

	//Create the window.
	window = SDL_CreateWindow(
		"Elder Bone Software -- Fractured Bone Game Engine", //Title
		800, //Width
		600, //Height
		0 //Locked size, change to SDL_WINDOW_RESIZABLE if you want a resizable window
	);

	//Make a renderer.
	renderer = SDL_CreateRenderer(window, nullptr);

	if (window == nullptr) {
		SDL_Quit();
		return -1;
	}

	//Initialize the text renderer.
	if (!TTF_Init()) {
		SDL_Log("TTF initialization failed: %s", SDL_GetError());
		return -1;
	}

	return 0;

}

//============================== GAME SETUP FUNCTIONS ====================================//

void Game::settingHowThePlayerShouldBeCalled(Player* player) {
	std::string setupName;
	bool nameConfirmed = false;

	writeText("ARIAL", 25, "TYPE YOUR NAME. AND PRESS ENTER!", 1, 1, { 255, 255, 255, 255 });
	render();

	SDL_StartTextInput(window);

	while (nameConfirmed == false && keepGameRunning == true) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_EVENT_TEXT_INPUT) {
				setupName += event.text.text;
			}

			if (event.type == SDL_EVENT_KEY_DOWN) {

				if (event.key.key == SDLK_BACKSPACE && !setupName.empty()) {
					setupName.pop_back();
				}

				if (event.key.key == SDLK_RETURN) {

					if (!setupName.empty()) {
						player->setPlayerName(setupName);
						nameConfirmed = true;
						break;
					}
				}
			}
		}
	}

	SDL_StopTextInput(window);

}

void Game::settingThePlayerGender(Player* player) {
	bool genderConfirmed = false;

	clearScreen();
	writeText("ARIAL", 25, "Is " + player->getPlayerName() + " male or female ? ", 1, 1, { 255, 255, 255, 255 });
	writeText("ARIAL", 25, "Press [1] for Male. Press [2] for Female", 1, 25, { 255, 255, 255, 255 });
	render();
	
	while (genderConfirmed == false && keepGameRunning == true) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_1) {
					player->setPlayerGender(Player::PlayerGender::MALE);
					genderConfirmed = true;
					break;
				}
				else if (event.key.key == SDLK_2) {
					player->setPlayerGender(Player::PlayerGender::FEMALE);
					genderConfirmed = true;
					break;
				}
			}
		}
	}

	if (genderConfirmed == true) {
		clearScreen();
		if (player->getPlayerGender() == Player::PlayerGender::MALE) {
			writeText("ARIAL", 25, player->getPlayerName() + " is male.", 1, 1, { 150, 255, 255, 255 });
		}
		else if (player->getPlayerGender() == Player::PlayerGender::FEMALE) {
			writeText("ARIAL", 25, player->getPlayerName() + " is female.", 1, 1, { 255, 200, 255, 255 });
		}
		render();
	}

}

void Game::settingThePlayerClass(Player* player, Pronouns* pronouns) {
	bool isPlayerClassConfirmed = false;

	delay(1);
	clearScreen();
	writeText("ARIAL", 25, "Great, now what class does " + pronouns->getLSubject(player) + " belongs to?",
		1, 1, { 255, 255, 255, 255 });
	writeText("ARIAL", 25, "Press[1] for knight, ", 1, 30, { 200, 200, 200, 255 });	
	writeText("ARIAL", 25, "[2] for Wizard, ", 220, 30, { 200, 255, 255, 255 });
	writeText("ARIAL", 25, "[3] for Bard, ", 385, 30, { 255, 255, 200, 255 });
	writeText("ARIAL", 25, "[4] for Noble", 525, 30, { 255, 200, 200, 255});
	writeText("ARIAL", 25, "or [5] for Wretch.", 1, 60, { 200, 255, 200, 255});
	render();

	while (isPlayerClassConfirmed == false) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_KEY_DOWN) {
				if (event.key.key == SDLK_1) {
					player->setPlayerClass(Player::PlayerClass::KNIGHT);
					isPlayerClassConfirmed = true;
					break;
				}
				else if (event.key.key == SDLK_2) {
					player->setPlayerClass(Player::PlayerClass::WIZARD);
					isPlayerClassConfirmed = true;
					break;
				}
				else if (event.key.key == SDLK_3) {
					player->setPlayerClass(Player::PlayerClass::BARD);
					isPlayerClassConfirmed = true;
					break;
				}
				else if (event.key.key == SDLK_4) {
					player->setPlayerClass(Player::PlayerClass::NOBLE);
					isPlayerClassConfirmed = true;
					break;
				}
				else if (event.key.key == SDLK_5) {
					player->setPlayerClass(Player::PlayerClass::WRETCH);
					isPlayerClassConfirmed = true;
					break;
				}
			}
		}
	}

	if (isPlayerClassConfirmed == true) {
		player->setPlayerAttributesAccordinglyToClass();
		player->vomitAllAttr();
	}
}


//========================================= GAME CORE =====================================//

void Game::setup(Game* game, Player* player, Pronouns* pronouns) {
	settingHowThePlayerShouldBeCalled(player);
	settingThePlayerGender(player);
	settingThePlayerClass(player, pronouns);
	
}

//Schedules All scenes. ADD EVERY SCENE HERE IN ORDER!
void Game::sceneScheduler(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	while (keepGameRunning == true) {
		setup(game, player, pronouns);
		firstScene.playScene(game, save, player, pronouns);
		scene1.playScene(game, save, player, pronouns);
	}
	
}

//Checks if there's a previous save and load based on the sceneID.
void Game::loadSceneFromSaveGame(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	//Fetch the scene ID of a previous save if there is one:
	int sceneID = loadGame(save);

	//Check the scene IDs to load proper scene.
	//ALL SCENES MUST BE HERE FOR A PROPER LOAD. Add "else if"s for new IDs.
	if (sceneID != 0) { 
		if (sceneID == scene1.getSceneID()) {
			scene1.playScene(game, save, player, pronouns);
		}
		else {
			//If none of the possible IDs match a scene, reload the setup.
			sceneScheduler(game, save, player, pronouns);
		}

	}
	else { //If there is no previous save, load the setup.
		sceneScheduler(game, save, player, pronouns);
	}
}

void Game::run(Game* game, Save* save, Player* player, Pronouns* pronouns) {
	makeWindow();
	loadSceneFromSaveGame(game, save, player, pronouns);
}

//THIS COMMAND KILLS THE GAME. ONLY USE IT IF THAT IS THE DESIRED FUNCTION.
void Game::stop() {
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();

	keepGameRunning = false;
}