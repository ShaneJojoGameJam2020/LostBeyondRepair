#include "TextDrawer.h"
#include "HelperFunctions.h"
#include "PlayerStatus.h"
#include <vector>
#include <iostream>
void TextDrawer::drawDay(std::vector<GameWorldObject *> worldObjects, std::pair<int, int> &playerLocation, PlayerStatus &status) {
	for (int i = 0; i < worldObjects.size(); i++) {
		std::pair<int, int> location = worldObjects[i]->getLocation();
		std::cout << worldObjects[i]->getName() << "is at location: " << location.first << ", " << location.second << std::endl;
	}

	std::cout << "Your location is: " << playerLocation.first << ", " << playerLocation.second << std::endl;
	std::cout << "You have " << status.curEnergy << "J engery" << std::endl;
	std::cout << "You can move up to " << status.getMaxMovementPerDay() << " distance" << std::endl;
	bool validLocationPicked = false;
	std::pair<int, int> pickedLocation;
	while (validLocationPicked == false) {
		//Enter it as x y
		
		std::cout << "Enter a location: " << std::endl;
		std::cin >> pickedLocation.first;
		std::cin >> pickedLocation.second;

		validLocationPicked = dayController.move(playerLocation, pickedLocation,status);
		if (validLocationPicked == true) {
			break;
		}
		std::cout << "Invalid location" << std::endl;
	}
}

void TextDrawer::drawNight() {

}

void TextDrawer::dropItem(std::vector<GameWorldObject> &worldObjects,std::pair<int,int> playerLocation, PlayerStatus &status) {
	
	if (status.inventoryFull == false) {
		return;
	}

	std::cout << "Would you like to drop your item: Y/N" << status.inventoryItem << "?" << std::endl;
	
	std::string response;
	std::cin >> response;
	if (response == "Y") {
		dropController.drop(worldObjects, playerLocation, status);
	}
}