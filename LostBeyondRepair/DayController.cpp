#include "DayController.h"
bool DayController::move(std::pair<int, int> &curLocation, std::pair<int, int> &targetLocation, PlayerStatus &status) {

	int distance = getTaxiCabDistance(curLocation, targetLocation);
	int totalUsableEnergy = status.getEngergyPerDay() + status.curEnergy;
	if (distance > status.getMaxMovementPerDay()) {
		return false;
	}
	if (distance > totalUsableEnergy) {
		return false;
	}
	status.curEnergy = totalUsableEnergy - distance;
	if (status.curEnergy > status.getMaxBattery()) {
		status.curEnergy = status.getMaxBattery();
	}
	curLocation = targetLocation;
	return true;
}