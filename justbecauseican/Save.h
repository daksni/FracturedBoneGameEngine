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

#pragma once
#include "Game.h";

class Save
{
public:

	struct SaveData {
		int sceneID;
		std::string playerName;
		int playerGender;
		int playerClass;
		int playerLife;
		//Add here things that must be saved.
	};

	SaveData saveData;

	bool load(std::string saveFileName);
	void save(std::string saveFileName);

};

