#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MiniGame {
public:
	virtual bool play(sf::RenderWindow& game) = 0;
};