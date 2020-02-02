
#include "Game.h"
#include "GameWorldObject.h"
#include <cstdlib>
#include <utility>
#include <ctime>
#include "HelperFunctions.h"
#include "TextDrawer.h"

void Game::init() {
	drawer = new TextDrawer;
	playerLocation.first = 0;
	playerLocation.second = 0;

	int partRange = 50;
	srand(time(NULL));
	worldObjects.reserve(numPartsNeeded);
	for (int i = 0; i < numPartsNeeded; i++) {
		int randNum1 = (rand() % (2 * partRange) - partRange);
		int randNum2 = (rand() % (2 * partRange) - partRange);
		std::string partName = "Part ";
		
		randNum1 /= (i + 1);
		randNum2 /= (i + 1);

		GameWorldObject obj(partName, randNum1, randNum2);
		worldObjects.push_back(obj);
	}
	int upgradeRange = 40;
	std::vector<int> zeroToThree;
	for (int i = 0; i < status.systems.size(); i++) {
		zeroToThree.push_back(i);
	}
	for (int i = 0; i < zeroToThree.size(); i++) {
		int newPos = rand() % zeroToThree.size();
		int oldValue = zeroToThree[i];
		zeroToThree[i] = zeroToThree[newPos];
		zeroToThree[newPos] = oldValue;
	}
	for (int i = 0; i < status.systems.size(); i++) {
		int randNum1 = (rand() %(2 * upgradeRange)) - upgradeRange;
		int randNum2 = (rand() % (2 * upgradeRange)) - upgradeRange;
		std::string upgradeName = "Upgrade ";

		randNum1 /= (zeroToThree[i] + 2);
		randNum2 /= (zeroToThree[i] + 2);
		upgradeName += status.systems[i].getName();
		GameWorldObject obj(upgradeName, randNum1, randNum2);
		worldObjects.push_back(obj);
	}

	status.inventoryItem = "";

	status.curEnergy = status.getMaxBattery();
	GameLoop();
}

void Game::dayCycle() {
		//Get the visable GameObjects and locations
	std:: vector<GameWorldObject *> visableObjects;
	int visableityRange = status.getSeeingDistance();
	for (int i = 0; i < worldObjects.size(); i++) {
		if (getTaxiCabDistance(worldObjects[i].getLocation(), playerLocation) < visableityRange) {
			
			if (playerLocation == worldObjects[i].getLocation()) {
				if (status.inventoryFull == false) {
					status.inventoryFull = true;
					status.inventoryItem = worldObjects[i].getName();
					worldObjects.erase(worldObjects.begin() + i);
					continue;
				}
			}
			visableObjects.push_back(&worldObjects[i]);
		}
	}
	drawer->dropItem(worldObjects, playerLocation, status);
	drawer->drawDay(visableObjects, playerLocation, status);
	if (playerLocation.first == 0 && playerLocation.second == 0) {
		if (status.inventoryFull == true) {
			if (status.inventoryItem == "Part") {
				numPartsFound++;
			}
			else if (status.inventoryItem.substr(0, 8) == "Upgrade ") {
				std::string upgradeType = status.inventoryItem.substr(8);
				for (int i = 0; i < status.systems.size(); i++) {
					if (upgradeType == status.systems[i].getName()) {
						status.systems[i].upgradeSystem();
						break;
					}
				}
			}
			if (numPartsFound == numPartsNeeded) {
				status.win = true;
			}
			status.inventoryFull = false;
			status.inventoryItem = "";
		}
		status.curEnergy = status.getMaxBattery();
		status.repair();
	}
	
}

void Game::GameLoop() {
	while (true) {
		dayCycle();
		nightCycle();
		if (status.win == true) {
			winState();
			break;
		}
		if (status.getMaxBattery() == 0 || status.getMaxMovementPerDay() == 0 || (status.getEngergyPerDay() == 0 && status.curEnergy == 0) ){
			loseState();
			break;
		}
	}
}

void Game::winState() {
	drawer->drawWin();
}
void Game::loseState() {
	drawer->drawLose();
}

void Game::nightCycle() {
	std::vector<int> failChecks;
	for (int i = 0; i < status.systems.size(); i++) {
		failChecks.push_back(status.systems[i].checkForBreakDown());
	}
	int highestFailCheck = 0;
	int highestFailCheckIndex = -1;
	for (int i = 0; i < failChecks.size(); i++) {
		if (failChecks[i] > highestFailCheck) {
			highestFailCheck = failChecks[i];
			highestFailCheckIndex = i;
		}
	}
	if (highestFailCheckIndex != -1) {
		status.systems[highestFailCheckIndex].breakDown();
	}
	drawer->drawMantience(status);
	status.incrementFailureChances();
}