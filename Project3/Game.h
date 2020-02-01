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

	
	PlayerStatus status;

	void GameLoop();
public: 
	void init();
};