#pragma once
#include <vector>
#include "GameWorldObject.h"
#include "PlayerStatus.h"
class DropController {
public:
	void drop(std::vector<GameWorldObject> &worldObjects, std::pair<int, int> playerLocation, PlayerStatus &status);
};