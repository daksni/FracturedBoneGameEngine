//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Game.h"
#include "FirstScene.h"
#include "Scene1.h"

//================================= AUXILIARY FUNCTIONS ===================================//

void Game::delay(int delayTime) {
	std::this_thread::sleep_for(std::chrono::seconds(delayTime));
}

//============================ CHECK FOR SAVE FILE =======================================//

int Game::loadGame() {
	SceneTemplate::SaveData saveData;
	std::ifstream saveFile("data.fbgesvdt");
	if (saveFile.is_open()) {
		saveFile >> saveData.sceneid;
		return saveData.sceneid;
	}
	else {
		return 0;
	}
}



//============================== GAME SETUP FUNCTIONS ====================================//

void Game::settingHowThePlayerShouldBeCalled(Player* player) {

	std::string setupName;

	std::cout << "Player's Name: ";
	std::getline(std::cin, setupName);

	while (setupName.empty()) {
		std::cout << "\nYou've given an incorrect input! Please try again.\nName: ";
		std::getline(std::cin, setupName);
	}

	player->setPlayerName(setupName);

}

void Game::settingThePlayerGender(Player* player) {

	const struct Gender {
		const std::string INPUT_MALE = "1";
		const std::string INPUT_FEMALE = "2";

		const int SELECT_MALE = 1;
		const int SELECT_FEMALE = 2;

	};

	Gender gender;

	std::string setupGender;

	std::cout << "\nIs " << player->getPlayerName() << " male or female?" << "\nType[1] for Male or [2] for Female: ";
	std::getline(std::cin, setupGender);

	while (setupGender.empty() || (setupGender != gender.INPUT_MALE && setupGender != gender.INPUT_FEMALE)) {
		std::cout << "\nYou've given an incorrect input! Please try again.\nType[1] for Male or [2] for Female: ";
		std::getline(std::cin, setupGender);
	}

	if (setupGender == gender.INPUT_MALE) {
		player->setPlayerGender(gender.SELECT_MALE);
	}
	else if (setupGender == gender.INPUT_FEMALE) {
		player->setPlayerGender(gender.SELECT_FEMALE);
	}

}

void Game::settingThePlayerClass(Player* player, Pronouns* pronouns) {

	std::string setupClass;

	const struct ClassWheel {
		const std::string INPUT_KNIGHT = "1";
		const std::string INPUT_WIZARD = "2";
		const std::string INPUT_BARD = "3";
		const std::string INPUT_NOBLE = "4";
		const std::string INPUT_WRETCH = "5";

	};

	ClassWheel classWheel;

	std::cout << "\nGreat, now what class does " << pronouns->getLSubject(player) <<
		" belongs to?\nType [1] for knight, [2] for Wizard, [3] for Bard, [4] for Noble or [5] for Wretch: ";
	std::getline(std::cin, setupClass);

	while (setupClass.empty() || (setupClass != classWheel.INPUT_KNIGHT &&
		setupClass != classWheel.INPUT_WIZARD &&
		setupClass != classWheel.INPUT_BARD &&
		setupClass != classWheel.INPUT_NOBLE &&
		setupClass != classWheel.INPUT_WRETCH)) {

		std::cout << "\nThe provided class is nonexistent! Please, choose again!";
		std::getline(std::cin, setupClass);

	}

	if (setupClass == classWheel.INPUT_KNIGHT) {
		player->setPlayerClass(player->PlayerClass::KNIGHT);
	}
	else if (setupClass == classWheel.INPUT_WIZARD) {
		player->setPlayerClass(player->PlayerClass::WIZARD);
	}
	else if (setupClass == classWheel.INPUT_BARD) {
		player->setPlayerClass(player->PlayerClass::BARD);
	}
	else if (setupClass == classWheel.INPUT_NOBLE) {
		player->setPlayerClass(player->PlayerClass::NOBLE);
	}
	else if (setupClass == classWheel.INPUT_WRETCH) {
		player->setPlayerClass(player->PlayerClass::WRETCH);
	}

	player->setPlayerAttributesAccordinglyToClass();
	player->vomitAllAttr();

}

//========================================= GAME CORE =====================================//

void Game::setup(Player* player, Pronouns* pronouns) {
	std::cout << "Hello, welcome to this prototype!\n";
	settingHowThePlayerShouldBeCalled(player);
	settingThePlayerGender(player);
	settingThePlayerClass(player, pronouns);
}

void Game::run(Player* player, Pronouns* pronouns) {
	//Fetch the scene ID of a previous save if there is one:
	int sceneID = loadGame();

	//Create an instance of every scene here:
	FirstScene firstScene;
	Scene1 scene1;

	//Checks if there's a previous save and load based on the sceneID.
	if (sceneID == 0) {
		setup(player, pronouns);
		firstScene.playScene(player, pronouns); //ALWAYS LOAD THE FIRST SCENE!
	}
	else if (sceneID != 0) { //Check the scene IDs to load proper scene. Add "else if"s for the other scenes.
		if (sceneID == firstScene.getSceneID()) {
			firstScene.playScene(player, pronouns);
		}
		else if (sceneID == scene1.getSceneID()) {
			scene1.playScene(player, pronouns);
		}
		else {
			//In case the sceneID doesn't match any scenes, load the setup.
			setup(player, pronouns);
			firstScene.playScene(player, pronouns); //ALWAYS LOAD THE FIRST SCENE!
		}
	}

}