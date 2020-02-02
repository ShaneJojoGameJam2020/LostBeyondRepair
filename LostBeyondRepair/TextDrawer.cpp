#include "TextDrawer.h"
#include "HelperFunctions.h"
#include "PlayerStatus.h"
#include <vector>
#include <iostream>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

void TextDrawer::drawMantience(PlayerStatus &status) {
	std::cout << "You have: " << status.curEnergy << "J Energy" << std::endl;
	std::cout << "Would you like to do a status report Y/N " << std::endl;
	std::string response;
	std::cin >> response;
	if (response == "Y") {
		std::vector<int> statusReport = mantienceController.statusReport(status);
		std::cout << "Radar Fail Chance: " << statusReport[0] << std::endl;
		std::cout << "Battery Fail Chance: " << statusReport[1] << std::endl;
		std::cout << "Energy Fail Chance: " << statusReport[2] << std::endl;
		std::cout << "Movement Fail Chance: " << statusReport[3] << std::endl;
	}
	while (mantienceController.getMantienceCost(status) <= status.curEnergy){
		std::cout << "You have: " << status.curEnergy << "J Energy" << std::endl;
		for (int i = 0; i < status.systems.size(); i++) {
			std::cout << i << ": " << status.systems[i].getName()<< std::endl;
		}
		std::cout << "Pick a system for mantience or -1 to break" << std::endl;
		int choice;
		std::cin >> choice;
		if (choice == -1) {
			break;
		}
		//mantienceController.mantienceSystem(status, choice);
	}
}

void TextDrawer::drawWin() {
	std::cout << "You Won!" << std::endl;
	while (true) {

	}
}

void TextDrawer::drawLose() {
	std::cout << "You Lost :(" << std::endl;
	while (true) {

	}
}
