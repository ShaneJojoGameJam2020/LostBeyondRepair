#pragma once
#include <utility>
#include "PlayerStatus.h"
#include "HelperFunctions.h"
class DayController {
public:
	
	bool move(std::pair<int, int> &curLocation, std::pair<int, int> &targetLocation, PlayerStatus &status);
};