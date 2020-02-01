#include "PlayerStatus.h"
	int PlayerStatus::getSeeingDistance() {
		return radarLvl * 200;
	}
	int PlayerStatus::getMaxBattery() {
		return batteryLvl * 100;
	}
	int PlayerStatus::getEngergyPerDay() {
		return energyLvl * 30;
	}

	int PlayerStatus::getMaxMovementPerDay() {
		return movementLvl * 40;
	}

