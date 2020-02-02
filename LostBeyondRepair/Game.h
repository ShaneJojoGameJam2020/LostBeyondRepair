#pragma once
#include<utility>
#include<vector>
#include "GameWorldObject.h"
#include "Drawer.h"
#include "MantienceController.h"
#include "DayController.h"
#include "DropController.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "RotationGame.h"



class Game {
	Drawer * drawer;

	std::vector<GameWorldObject *> dayStart();
	void dayInput();
	void nightStart(sf::RenderWindow &window);
	void nightInput(int index);
	std::pair<int,int> playerLocation;

	std::vector<GameWorldObject> worldObjects;

	DayController dayControl;
	DropController dropControl;
	MantienceController maintenanceControl;

	
	int numPartsNeeded = 3;
	int numPartsFound = 0;

	PlayerStatus status;

	void GameLoop(sf::RenderWindow& window);
	void winState();
	void loseState();

public: 
	void Intro(sf::RenderWindow& game);
	void MainMenu(sf::RenderWindow& game);
	bool RadarGame(sf::RenderWindow& game);
	void init();
};