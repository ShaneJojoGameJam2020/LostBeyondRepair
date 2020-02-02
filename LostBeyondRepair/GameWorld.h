#pragma once
#include "GameWorldObject.h"
#include <vector>

class GameWorld {
	std::vector<GameWorldObject> worldObjects;

	void init();
	void movePlayer();

	

};