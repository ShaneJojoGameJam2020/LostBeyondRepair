#pragma once
#include "GameWorldObject.h"
#include<utility>
#include<vector>
#include "PlayerStatus.h"
#include "DayController.h"
#include "DropController.h"
#include "MantienceController.h"
class Drawer {
protected:
	DayController dayController;
	DropController dropController;
	MantienceController mantienceController;
public:
	//Draw day takes in the vector visableObjects and the player's location, it will prompt the player to move and update their location based on their movement choice
	virtual	void drawDay(std::vector<GameWorldObject *> visableObjects,  std::pair<int,int> &playerLocation, PlayerStatus &status)  = 0;
	
	virtual void dropItem(std::vector<GameWorldObject> &worldObjects,std::pair<int,int> playerLocation, PlayerStatus &status) = 0;
	virtual void drawMantience(PlayerStatus &systems) = 0;
	virtual void drawWin() = 0;
	virtual void drawLose() = 0;
};