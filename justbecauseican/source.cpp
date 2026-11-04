//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Game.h"

int main() {
	//If any new pointer is made, declare them here.
	Player* player = new Player();
	Pronouns* pronouns = new Pronouns();

	Game game;
	game.run(player, pronouns);

	//Delete and Nullify pointers.

	delete player;
	player = nullptr;

	delete pronouns;
	pronouns = nullptr;

	return 0;
}
