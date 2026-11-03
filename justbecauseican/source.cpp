//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Game.h"

int main() {
	Game game;
	if (game.loadGame() == 0) {
		game.run();
	}
	else {
		std::cout << "It appears we have a save file!"; //do things later
	}
	
}
