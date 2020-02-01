#pragma once
#include<string>
#include<utility>

class GameWorldObject {

	std::pair<int, int> location;

	std::string name;
public:	

	GameWorldObject(std::string name, int x, int y);	
	std::pair<int, int> getLocation();
	std::string getName();
		
};