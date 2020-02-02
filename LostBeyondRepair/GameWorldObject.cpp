#include "GameWorldObject.h"
#include <utility>

GameWorldObject::GameWorldObject(std::string name, int x, int y) {
	this->name = name;
	location.first = x;
	location.second = y;
}

std::pair<int,int> GameWorldObject::getLocation() {
	return location;
}

std::string GameWorldObject::getName() {
	return name;
}
