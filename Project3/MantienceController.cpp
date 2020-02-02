#include "MantienceController.h"
#include "PlayerStatus.h"
#include <vector>
bool MantienceController::mantienceSystem(PlayerStatus &status, int index) {
	int mantienceCost = 1;
	if (status.curEnergy < mantienceCost) {
		return false;
	}
	
	status.systems[index].doMantenice();
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