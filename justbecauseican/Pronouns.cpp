//This code is property of Elder Bone Software.
//Developed by Lead Engine Programmer: Daniel M. S. A.
//The usage of this code freely is allowed as long as the author is credited.

#include "Pronouns.h"

const enum SelectedGender {
	MALE = 1,
	FEMALE = 2
};

//Capitalized
std::string Pronouns::getCSubject(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mCSubject;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fCSubject;
	}

}

std::string Pronouns::getCObject(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mCObject;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fCObject;
	}

}

std::string Pronouns::getCPossesive(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mCPossesive;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fCObject;
	}
}

//Lowercase
std::string Pronouns::getLSubject(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mLSubject;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fLSubject;
	}
}

std::string Pronouns::getLObject(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mLObject;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fLObject;
	}

}

std::string Pronouns::getLPossesive(Player* player) const {
	if (player->getPlayerGender() == SelectedGender::MALE) {
		return mLPossesive;
	}
	else if (player->getPlayerGender() == SelectedGender::FEMALE) {
		return fLObject;
	}

}
