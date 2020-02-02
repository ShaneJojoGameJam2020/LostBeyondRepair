#pragma once
#include <vector>
#include "GameWorldObject.h"
#include "Drawer.h"
#include "PlayerStatus.h"
#include "DayController.h"
class TextDrawer : public Drawer {
	
	
	void dropItem(std::vector<GameWorldObject> &worldObjects,std::pair<int,int> playerLocation, PlayerStatus &status);
	void drawDay(std::vector<GameWorldObject *> visableObjects, std::pair<int, int> &PlayerLocation, PlayerStatus &status);
	void drawMantience(PlayerStatus &status);
	void drawWin();
	 void drawLose();
};
