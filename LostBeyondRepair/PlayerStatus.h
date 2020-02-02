#pragma once
#include <string>
#include <vector>
#include "RobotSystem.h"
class PlayerStatus {

	

public:
	bool win;
	std::vector<RobotSystem> systems;
	PlayerStatus();
	int getSeeingDistance();
	int getMaxBattery();
	int getEngergyPerDay();
	int getMaxMovementPerDay();
	int curEnergy;
	std::string inventoryItem = "";
	bool inventoryFull = false;
	int turnsSinceBase = 0;
	void incrementFailureChances();
	void repair();
};