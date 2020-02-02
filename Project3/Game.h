#pragma once
#include<utility>
#include<vector>
#include "GameWorldObject.h"
#include "Drawer.h"



class Game {
	Drawer * drawer;

	void dayCycle();
	void nightCycle();
	std::pair<int,int> playerLocation;

	std::vector<GameWorldObject> worldObjects;

	
	int numPartsNeeded = 3;
	int numPartsFound = 0;

	PlayerStatus status;

	void GameLoop();
	void winState();
	void loseState();
public: 
	void init();
};