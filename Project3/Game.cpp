
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

	srand(time(NULL));
	worldObjects.reserve(3);

	int randNum1 = (rand() % 2000) - 1000;
	int randNum2 = (rand() % 2000) - 1000;
	
	GameWorldObject obj("Part 1", randNum1, randNum2);
	worldObjects.push_back(obj);

	 randNum1 = (rand() % 2000) - 1000;
	 randNum2 = (rand() % 2000) - 1000;

	 obj = GameWorldObject("Part 2", randNum1, randNum2);
	worldObjects.push_back(obj);

	 randNum1 = (rand() % 2000) - 1000;
	 randNum2 = (rand() % 2000) - 1000;

	 obj = GameWorldObject("Part 3", randNum1, randNum2);
	worldObjects.push_back(obj);
	worldObjects.push_back(GameWorldObject("Part 4", 10,10));
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
}

void Game::GameLoop() {
	while (true) {
		dayCycle();
		nightCycle();
	}
}

void Game::nightCycle() {

}