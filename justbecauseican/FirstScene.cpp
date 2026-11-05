//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is the FirstScene, configure in here what is the first thing that happens in the game.

#include "Game.h"
#include "FirstScene.h"

void FirstScene::playScene(Game* game, Player* player, Pronouns* pronouns) {
	std::string choice;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	//delay(3);
	std::cout << "Welcome to this empty scene!\nPress [1] to go to the next scene. \tPress [2] to quit the game.\n";
	std::getline(std::cin, choice);
	while (choice.empty() || choice != "1" && choice != "2") {
		std::cout << "\nInvalid input. Press [1] to go to the next scene.\n";
		std::getline(std::cin, choice);
	}

	if (choice == "1") {
		genNewSave(player);
	}
	else if (choice == "2") {
		game->keepGameRunning = false;
	}

}


void FirstScene::genNewSave(Player* player) {
	FirstScene::SaveData saveData;

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

int const FirstScene::getSceneID() {
	return SCENE_ID;
}