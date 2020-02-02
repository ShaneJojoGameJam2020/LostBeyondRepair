#pragma once
#include "RobotSystem.h"
#include <string>
#include <ctime>
int RobotSystem::checkForBreakDown() {
	int roll = rand() % 100;
	return roll + breakDownChance - 100;
}

void RobotSystem::resetBreakDownChance() {
	breakDownChance = 0;
}

void RobotSystem::doMantenice(sf::RenderWindow &window){
	bool result = manteniceGame->play(window);
	if (result == true) {
		breakDownChance = breakDownChance / 2;
	}
}

bool RobotSystem::breakDown(sf::RenderWindow &window) {
	bool result = saveingGame->play(window);
	if (result == false) {
		curHealth--;
	}
	breakDownChance = breakDownChance / 2;
	return result;
}

int RobotSystem::getStat() {
	return statWeight * Lvl * ((float)curHealth / (float)maxHealth);
}

RobotSystem::RobotSystem(std::string name, int maxHealth, int statWeight, MiniGame * manteniceGame, MiniGame * savingGame) {
	this -> name = name;
	this->maxHealth = maxHealth;
	this->curHealth = maxHealth;
	this->statWeight = statWeight;
	this->manteniceGame = manteniceGame;
	this->saveingGame = savingGame;
	Lvl = 1;

}

void RobotSystem::increaseBreakDownChance() {
	breakDownChance += rand() % 10;
}

void RobotSystem::repairSystem() {
	curHealth = maxHealth;
}

void RobotSystem::upgradeSystem() {
	Lvl++;
}