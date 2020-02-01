#pragma once
#include <string>
class PlayerStatus {
	int energyLvl = 1;
	int batteryLvl = 1;
	int movementLvl = 1;
	int radarLvl = 1;
	
public:
	int getSeeingDistance();
	int getMaxBattery();
	int getEngergyPerDay();
	int getMaxMovementPerDay();
	int curEnergy;
	std::string inventoryItem = "";
	bool inventoryFull = false;
};