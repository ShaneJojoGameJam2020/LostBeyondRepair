#pragma once

#include "PlayerStatus.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class MantienceController {
public:
	bool mantienceSystem(PlayerStatus &stauts, int index, sf::RenderWindow &window);
	std::vector<int> statusReport(PlayerStatus &status);
	int getMantienceCost(PlayerStatus &status);
};