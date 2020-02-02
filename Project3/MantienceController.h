#pragma once

#include "PlayerStatus.h"

class MantienceController {
public:
	bool mantienceSystem(PlayerStatus &stauts, int index);
	std::vector<int> statusReport(PlayerStatus &status);
	int getMantienceCost(PlayerStatus &status);
};