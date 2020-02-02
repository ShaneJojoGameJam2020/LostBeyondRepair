#include "PlayerStatus.h"
#include "TestMiniGame.h"
	int PlayerStatus::getSeeingDistance() {
		return systems[0].getStat();
	}
	int PlayerStatus::getMaxBattery() {
		return systems[1].getStat();
	}
	int PlayerStatus::getEngergyPerDay() {
		return systems[2].getStat();
	}

	int PlayerStatus::getMaxMovementPerDay() {
		return systems[3].getStat();
	}

	PlayerStatus::PlayerStatus() {
		TestMiniGame * testGame = new TestMiniGame;
		RobotSystem radar("radar", 2, 20, testGame, testGame);
		RobotSystem battery("battery", 4, 10, testGame, testGame);
		RobotSystem energy("energy", 3, 4, testGame, testGame);
		RobotSystem movement("movement", 3, 8, testGame, testGame);
		systems.push_back(radar);
		systems.push_back(battery);
		systems.push_back(energy);
		systems.push_back(movement);
}

	void PlayerStatus::incrementFailureChances() {
		for (int i = 0; i < systems.size(); i++) {
			systems[i].increaseBreakDownChance();
		}
}

	void PlayerStatus::repair() {
		for (int i = 0; i < systems.size(); i++) {
			systems[i].repairSystem();
			systems[i].resetBreakDownChance();
		}
}