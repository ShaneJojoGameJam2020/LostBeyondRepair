#pragma once
#include "DropController.h"
#include <vector>
#include "PlayerStatus.h"
#include "GameWorldObject.h"
void DropController::drop(std::vector<GameWorldObject> &worldObjects, std::pair<int, int> playerLocation, PlayerStatus &status) {
	GameWorldObject obj(status.inventoryItem, playerLocation.first, playerLocation.second);
	worldObjects.push_back(obj);
	status.inventoryFull = false;

}