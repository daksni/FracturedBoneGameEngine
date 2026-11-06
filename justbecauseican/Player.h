//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#pragma once

#include <string>
#include <iostream>


class Player
{
private:

	//Player Attribiutes || Statuses
	int playerLife;
	std::string playerName;
	bool isPlayerDead;
	int playerGender;
	int playerClass;

public:

	//Enumeration of possible player classes.
	const enum PlayerClass {
		KNIGHT = 1,
		WIZARD = 2,
		BARD = 3,
		NOBLE = 4,
		WRETCH = 5
	};

	//Enumeration of possible player genders.
	const enum PlayerGender {
		MALE = 1,
		FEMALE = 2
	};

	//Getter arguments.
	int getPlayerLife() const;
	std::string getPlayerName() const;
	bool getIsPlayerDead() const;
	int getPlayerGender() const;
	int getPlayerClass() const;

	//Setter arguments.
	void setPlayerLife(int life);
	void setPlayerName(std::string name);
	void setIsPlayerDead(bool localIsPlayerDead);
	void setPlayerGender(int gender);
	void setPlayerClass(int pClass);

	void setPlayerAttributesAccordinglyToClass();

	void vomitAllAttr();
};

