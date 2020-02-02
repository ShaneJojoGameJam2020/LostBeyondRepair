#include "TestMiniGame.h"

bool TestMiniGame::play(sf::RenderWindow& game) {
	int roll = rand();
	if (roll % 100 <= 80) {
		std::cout << "System failure avoided" << std::endl;
		return true;
	}
	else {
		std::cout << "System failure occured" << std::endl;
		return false;
	}
}