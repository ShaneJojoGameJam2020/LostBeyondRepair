#include "MantienceController.h"
#include "PlayerStatus.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
bool MantienceController::mantienceSystem(PlayerStatus &status, int index,sf::RenderWindow &window) {
	int mantienceCost = 1;
	if (status.curEnergy < mantienceCost) {
		return false;
	}
	
	status.systems[index].doMantenice(window);
	status.curEnergy -= mantienceCost;
		return true;
}

int MantienceController::getMantienceCost(PlayerStatus &status) {
	return 1 + status.turnsSinceBase;
}

std::vector<int> MantienceController::statusReport(PlayerStatus &status) {
	std::vector<int> returnVec;
	for (int i = 0; i < status.systems.size(); i++) {
		returnVec.push_back(status.systems[i].getBreakDownChance());
	}
	status.curEnergy -= 2;
	if (status.curEnergy < 0) {
		status.curEnergy = 0;
	}
	return returnVec;

}