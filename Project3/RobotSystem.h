#pragma once
#include <string>
#include "MiniGame.h"
class RobotSystem {
	std::string name;
	int Lvl;
	int maxHealth;
	int curHealth;
	int breakDownChance;
	MiniGame * manteniceGame;
	MiniGame * saveingGame;
	int statWeight;
public:
	void increaseBreakDownChance();
	int checkForBreakDown();
	void resetBreakDownChance();
	void doMantenice();
	bool breakDown();
	int getStat();
	RobotSystem() {}
	RobotSystem(std::string name, int maxHealth, int statWeight, MiniGame * manteniceGame, MiniGame * saveingGame);
	int getBreakDownChance() { return breakDownChance; }
	std::string getName() { return name; }
	void repairSystem();
	void upgradeSystem();
};