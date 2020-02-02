
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <vector>
#include "Game.h"
#include "GameWorldObject.h"
#include <cstdlib>
#include <utility>
#include <ctime>
#include "HelperFunctions.h"
#include "TextDrawer.h"
#include <iostream>
#include "RotationGame.h"
using namespace std;

void Game::init() {
	drawer = new TextDrawer;
	playerLocation.first = 0;
	playerLocation.second = 0;

	int partRange = 50;
	srand(time(NULL));
	worldObjects.reserve(numPartsNeeded);
	for (int i = 0; i < numPartsNeeded; i++) {
		int randNum1 = (rand() % (2 * partRange) - partRange);
		int randNum2 = (rand() % (2 * partRange) - partRange);
		std::string partName = "Part ";
		
		randNum1 /= (i + 1);
		randNum2 /= (i + 1);

		GameWorldObject obj(partName, randNum1, randNum2);
		worldObjects.push_back(obj);
	}
	int upgradeRange = 40;
	std::vector<int> zeroToThree;
	for (int i = 0; i < status.systems.size(); i++) {
		zeroToThree.push_back(i);
	}
	for (int i = 0; i < zeroToThree.size(); i++) {
		int newPos = rand() % zeroToThree.size();
		int oldValue = zeroToThree[i];
		zeroToThree[i] = zeroToThree[newPos];
		zeroToThree[newPos] = oldValue;
	}
	for (int i = 0; i < status.systems.size(); i++) {
		int randNum1 = (rand() %(2 * upgradeRange)) - upgradeRange;
		int randNum2 = (rand() % (2 * upgradeRange)) - upgradeRange;
		std::string upgradeName = "Upgrade ";

		randNum1 /= (zeroToThree[i] + 2);
		randNum2 /= (zeroToThree[i] + 2);
		upgradeName += status.systems[i].getName();
		GameWorldObject obj(upgradeName, randNum1, randNum2);
		worldObjects.push_back(obj);
	}

	status.inventoryItem = "";

	status.curEnergy = status.getMaxBattery();

	sf::RenderWindow game(sf::VideoMode(1000, 700), "Lost Beyond Repair", sf::Style::Close);
	sf::View view(sf::FloatRect((float)0, (float)0, (float)game.getSize().x, (float)game.getSize().y));
	game.setView(view);
	game.setFramerateLimit(24);
	game.setMouseCursorVisible(true);

	RotationGame rGame;
	rGame.play(game);

	Intro(game);
	MainMenu(game);

	GameLoop(game);

}

std::vector<GameWorldObject *> Game::dayStart() {

		//Get the visable GameObjects and locations
	std:: vector<GameWorldObject *> visableObjects;
	int visableityRange = status.getSeeingDistance();
	for (int i = 0; i < worldObjects.size(); i++) {
		if (getTaxiCabDistance(worldObjects[i].getLocation(), playerLocation) < visableityRange) {

			if (playerLocation == worldObjects[i].getLocation()) {
				if (status.inventoryFull == false) {
					status.inventoryFull = true;
					status.inventoryItem = worldObjects[i].getName();
					worldObjects.erase(worldObjects.begin() + i);
					continue;
				}
			}
			visableObjects.push_back(&worldObjects[i]);
		}
	}
	return visableObjects;
}
	
void Game::dayInput() {

	if (playerLocation.first == 0 && playerLocation.second == 0) {
		if (status.inventoryFull == true) {
			if (status.inventoryItem == "Part") {
				numPartsFound++;
			}
			else if (status.inventoryItem.substr(0, 8) == "Upgrade ") {
				std::string upgradeType = status.inventoryItem.substr(8);
				for (int i = 0; i < status.systems.size(); i++) {
					if (upgradeType == status.systems[i].getName()) {
						status.systems[i].upgradeSystem();
						break;
					}
				}
			}
			if (numPartsFound == numPartsNeeded) {
				status.win = true;
			}
			status.inventoryFull = false;
			status.inventoryItem = "";
		}
		status.curEnergy = status.getMaxBattery();
		status.repair();
	}
	
}

void Game::GameLoop(sf::RenderWindow& game) {

	int radius = 20;

	sf::Texture upgrade;
	upgrade.loadFromFile("assets/upgrade.png");

	sf::Texture part;
	part.loadFromFile("assets/part.png");

	sf::Texture map;
	map.loadFromFile("assets/grid.png");

	sf::Texture tstatus;
	tstatus.loadFromFile("assets/statusMenu.png");

	sf::Texture yes;
	yes.loadFromFile("assets/yes.png");

	sf::Texture no;
	no.loadFromFile("assets/no.png");

	sf::Sprite sStatus;
	sStatus.setTexture(tstatus);
	sStatus.setOrigin((float)sStatus.getTextureRect().width / 2, (float)sStatus.getTextureRect().height / 2);
	sStatus.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);

	sf::Sprite sMap;
	sMap.setTexture(map);
	sMap.setOrigin((float)sMap.getTextureRect().width / 2, (float)sMap.getTextureRect().height / 2);
	sMap.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	sMap.setScale(3.75, 3.75);
	sMap.setRotation(45);

	sf::Sprite sDo;
	sDo.setTexture(yes);
	sDo.setOrigin((float)sDo.getTextureRect().width / 2, (float)sDo.getTextureRect().height / 2);
	sDo.setPosition(800, 600);
	sDo.setScale(4, 2);

	string pos = "(" + to_string(sf::Mouse::getPosition(game).x) + ", " + to_string(sf::Mouse::getPosition(game).y) + ")";

	sf::Text coords;;
	sf::Font anon;
	anon.loadFromFile("assets/fonts/AnonymousPro-Regular.ttf");
	coords.setFont(anon);
	coords.setString(pos);
	coords.setFillColor(sf::Color::White);
	coords.setCharacterSize(28);
	coords.setPosition(sf::Mouse::getPosition(game).x + 5, sf::Mouse::getPosition(game).y);

	sf::Text doText;
	doText.setFont(anon);
	doText.setString("Do Maintenance");
	doText.setFillColor(sf::Color::Black);
	doText.setCharacterSize(28);
	doText.setPosition(700, 578);

	sf::Text power;
	power.setFont(anon);
	power.setString("Power" + to_string(status.curEnergy) + "J");
	power.setFillColor(sf::Color::White);
	power.setCharacterSize(28);
	power.setPosition(700, 50);

	sf::Text maxMovement;
	maxMovement.setFont(anon);
	maxMovement.setString("Movement: " + to_string(status.getMaxMovementPerDay()) + " Units");
	maxMovement.setFillColor(sf::Color::White);
	maxMovement.setCharacterSize(28);
	maxMovement.setPosition(700, 80);

	sf::Text maxBattery;
	maxBattery.setFont(anon);
	maxBattery.setString("Max Battery: " + to_string(status.getMaxBattery()) + "J");
	maxBattery.setFillColor(sf::Color::White);
	maxBattery.setCharacterSize(28);
	maxBattery.setPosition(700, 110);

	sf::Text maxRecharge;
	maxRecharge.setFont(anon);
	maxRecharge.setString("Recharge Rate: " + to_string(status.getEngergyPerDay()) + "J");
	maxRecharge.setFillColor(sf::Color::White);
	maxRecharge.setCharacterSize(28);
	maxRecharge.setPosition(700, 140);

	sf::Text maxRadar;
	maxRadar.setFont(anon);
	maxRadar.setString("Radar: " + to_string(status.getSeeingDistance()) + " Units");
	maxRadar.setFillColor(sf::Color::White);
	maxRadar.setCharacterSize(28);
	maxRadar.setPosition(700, 170);

	bool renderObjects = true;
	bool isDay = true;
	bool doMain = false;
	std::vector<sf::Sprite> visible;

	while (game.isOpen()) {

			//Get and display coordinates
		int mouseX = (sf::Mouse::getPosition(game).x - 500) / (300 / radius) + playerLocation.first;
		int mouseY = (350 - sf::Mouse::getPosition(game).y) / (300 / radius) + playerLocation.second;

			string pos = "(" + to_string(mouseX) + ", " + to_string(mouseY) + ")";
			coords.setString(pos);
			coords.setPosition(sf::Mouse::getPosition(game).x, sf::Mouse::getPosition(game).y);

			if (isDay) {

				std::vector<GameWorldObject * > visObj = dayStart();

				if (renderObjects)
				for (int i = 0; i < visObj.size(); i++)
				{
					if (visObj[i]->getName().substr(0,8) =="Upgrade ")
					{

						cout << "SOMETHING AT" << + visObj[i]->getLocation().first << ", " << visObj[i]->getLocation().second << endl;
						sf::Sprite newSprite;
						newSprite.setTexture(upgrade);
						newSprite.setOrigin((float)newSprite.getTextureRect().width / 2, (float)newSprite.getTextureRect().height / 2);
						newSprite.setPosition((visObj[i]->getLocation().first - playerLocation.first) * 300/radius + 500, 350 - ((visObj[i]->getLocation().second - playerLocation.second) * 300/radius));
						newSprite.setScale(2, 2);
						visible.push_back(newSprite);

					}

				}

				renderObjects = false;

				sf::Event event;
				while (game.pollEvent(event) && isDay)
				{

					if (event.type == sf::Event::MouseButtonPressed)
						if (event.key.code == sf::Mouse::Left)
						{

							bool clickedSomething = false;
							int clicked = 0;

							for (int i = 0; i < visible.size(); i++)
							{
								if (visible[i].getGlobalBounds().contains(game.mapPixelToCoords(sf::Mouse::getPosition(game))))
								{
									cout << "CLICKED AN OBJECT" << endl;
									clickedSomething = true;
									clicked = i;
								}
							}

							if (clickedSomething)
							{

								std::pair<int, int> location; //Represents where the mouse clicks
								location.first = (visible[clicked].getPosition().x - 500) / (300 / radius) + playerLocation.first;
								location.second = (350 - visible[clicked].getPosition().y) / (300 / radius) + playerLocation.second;
								bool isVaildLocation = dayControl.move(playerLocation, location, status);
								cout << "COORDS: " << location.first << " " << location.second << endl;
								if (isVaildLocation)
								{
									dayInput();
									isDay = !isDay;
									cout << "VALID" << endl;
									renderObjects = true;

									visible.erase(visible.begin(), visible.end());

								}
								else cout << "INVALID" << endl;

							}
							else
							{
								cout << "CLICK!" << endl;
								std::pair<int, int> location; //Represents where the mouse clicks
								location.first = (sf::Mouse::getPosition(game).x - 500) / (300 / radius) + playerLocation.first;
								location.second = (350 - sf::Mouse::getPosition(game).y) / (300 / radius) + playerLocation.second;
								bool isVaildLocation = dayControl.move(playerLocation, location, status);
								if (isVaildLocation)
								{
									dayInput();
									isDay = !isDay;
									cout << "VALID" << endl;
									renderObjects = true;

									visible.erase(visible.begin(), visible.end());

								}
								else cout << "INVALID" << endl;

							}

						}

				}

				if (!isDay && doMain) {

					cout << "NIGHT TIME" << endl;

					//Pass window into nightStart
					nightStart(game);

					sf::Event event;
					while (game.pollEvent(event) && isDay)
					{

						if (event.type == sf::Event::MouseButtonPressed)
							if (event.key.code == sf::Mouse::Left)
							{


								if (/*Clicked on status report*/ false) {
									maintenanceControl.statusReport(status);
								}
								if (/*Clicked on maintience*/ false) {
									int index = 0; //Set Index to appropirate system
									maintenanceControl.mantienceSystem(status, index,game);
								}
								if (/*Clicked on exit*/ false) {
									isDay = !isDay;
								}

							}

					}

				}

			}

			if (status.win == true) {
				winState();
				break;
			}
			if (status.getMaxBattery() == 0 || status.getMaxMovementPerDay() == 0 || (status.getEngergyPerDay() == 0 && status.curEnergy == 0)) {
				loseState();
				break;
			}


		power.setString("Power: " + to_string(status.curEnergy) + "J");
		maxMovement.setString("Movement: " + to_string(status.getMaxMovementPerDay()) + " Units");
		maxBattery.setString("Max Battery: " + to_string(status.getMaxBattery()) + "J");
		maxRecharge.setString("Recharge Rate: " + to_string(status.getEngergyPerDay()) + "J");
		maxRadar.setString("Radar: " + to_string(status.getSeeingDistance()) + " Units");

		game.clear(sf::Color(50, 50, 50, 255));
		game.draw(sMap);

		for (int i = 0; i < visible.size(); i++)
		{
			game.draw(visible[i]);
		}

		game.draw(power);
		game.draw(maxMovement);
		game.draw(maxRadar);
		game.draw(maxRecharge);
		game.draw(maxBattery);
		game.draw(sDo);
		game.draw(doText);

		if (!isDay && doMain) game.draw(sStatus);

		if(abs(mouseX) + abs(mouseY) < radius)
			game.draw(coords);

		game.display();

	}

}

void Game::winState() {
	drawer->drawWin();
}
void Game::loseState() {
	drawer->drawLose();
}

void Game::nightStart(sf::RenderWindow &window) {
	std::vector<int> failChecks;
	for (int i = 0; i < status.systems.size(); i++) {
		failChecks.push_back(status.systems[i].checkForBreakDown());
	}
	int highestFailCheck = 0;
	int highestFailCheckIndex = -1;
	for (int i = 0; i < failChecks.size(); i++) {
		if (failChecks[i] > highestFailCheck) {
			highestFailCheck = failChecks[i];
			highestFailCheckIndex = i;
		}
	}
	if (highestFailCheckIndex != -1) {
		status.systems[highestFailCheckIndex].breakDown(window);
	}
}

void Game::Intro(sf::RenderWindow& game)
{

	int clock = 0;

	sf::Texture cutscene1;
	cutscene1.loadFromFile("assets/cutscene1.png");

	sf::Texture cutscene2;
	cutscene2.loadFromFile("assets/cutscene2.png");

	sf::Texture cutscene3;
	cutscene3.loadFromFile("assets/cutscene3.png");

	sf::Texture cutscene35;
	cutscene35.loadFromFile("assets/cutscene3.5.png");

	sf::Texture cutscene4;
	cutscene4.loadFromFile("assets/cutscene4.png");

	sf::Texture cutscene5;
	cutscene5.loadFromFile("assets/cutscene5.png");

	sf::Sprite scene;
	scene.setTexture(cutscene1);
	scene.setOrigin((float)scene.getTextureRect().width / 2, (float)scene.getTextureRect().height / 2);
	scene.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	scene.setScale(2, 2);

	sf::Music introSong;
	introSong.openFromFile("assets/Isolated.ogg");
	introSong.play();


	while (game.isOpen())
	{
		if (clock >= 0) clock++;

		if (clock == 288)
		{
			scene.setTexture(cutscene2);
		}

		if (clock == 460)
			scene.setTexture(cutscene3);

		if (clock == 600)
			scene.setTexture(cutscene35);

		if (clock == 612)
			scene.setTexture(cutscene4);

		if (clock == 820)
			scene.setTexture(cutscene5);

		if (clock == 1200)
		{
			clock = -1;
			introSong.stop();
		}


		sf::Event event;
		while (game.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Enter)
					return;
			}


		}

		game.clear(sf::Color::Black);
		game.draw(scene);
		game.display();

	}

}

void Game::MainMenu(sf::RenderWindow& game)
{

	int option = 0;

	sf::Texture cutscene5;
	cutscene5.loadFromFile("assets/cutscene5.png");

	sf::Sprite scene;
	scene.setTexture(cutscene5);
	scene.setOrigin((float)scene.getTextureRect().width / 2, (float)scene.getTextureRect().height / 2);
	scene.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	scene.setScale(2, 2);

	sf::Texture start;
	start.loadFromFile("assets/start.png");

	sf::Sprite sStart;
	sStart.setTexture(start);
	sStart.setOrigin(0, 0);
	sStart.setPosition((float)700, (float)275);
	sStart.setScale(.5, .5);

	sf::Texture point;
	point.loadFromFile("assets/pointer.png");

	sf::Sprite sPoint;
	sPoint.setTexture(point);
	sPoint.setOrigin(0, 0);
	sPoint.setPosition((float)650, (float)300);
	sPoint.setScale(.5, .5);


	while (game.isOpen())
	{

		sf::Event event;
		while (game.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Enter)
				{
					if (option == 0) return;
					else exit(0);
				}

				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
				{
					if (option == 1) option = 0;
					sPoint.setPosition(650, 300);
				}

				if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
				{
					if (option == 0) option = 1;
					sPoint.setPosition(650, 375);
				}
			}


		}

		game.clear(sf::Color::Black);
		game.draw(scene);
		game.draw(sStart);
		game.draw(sPoint);
		game.display();

	}


}

