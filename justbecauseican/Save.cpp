//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

//This is the global save system. For it to work properly, you must add every
//information you wish to save, on the SaveData struct, on load(), and on save().
//This will allow you to write save files with all the information needed.


//When using load on a scene, you'll be able to push ONLY the information you wish.
//As well, as only defining the values of the things you want to save; by extracting the information
// from the struct.

//You can also make different save files by changing the name of the save.
//This allows you to make different files, for either backups or new games.

#include "Save.h"


bool Save::load(std::string saveFileName) {
	std::ifstream saveFile(saveFileName + ".fbgesvdt");
	if (saveFile.is_open()) {
		saveFile >> saveData.sceneID;
		//std::getline(saveFile >> std::ws, saveData.playerName);
		//saveFile >> saveData.playerGender;
		//saveFile >> saveData.playerClass;
		saveFile >> saveData.playerLife;

		return true;
	}
	else {
		std::cout << "THE SPECIFIED SAVE FILE WAS NOT FOUND!";
		return false;
	}
}

void Save::save(std::string saveFileName) {
	std::ofstream saveFile(saveFileName + ".fbgesvdt");
	saveFile << saveData.sceneID << "\n";
	//saveFile << saveData.playerName << "\n";
	//saveFile << saveData.playerGender << "\n";
	//saveFile << saveData.playerClass << "\n";
	saveFile << saveData.playerLife << "\n";
}