#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
#include <vector>
#include "Game.h"
using namespace std;



int main()
{

	Game game;
	game.init();

	return 0;

}




void Dashboard(sf::RenderWindow& game)
{

	int radius = 20;

	sf::Texture map;
	map.loadFromFile("assets/grid.png");

	sf::Sprite sMap;
	sMap.setTexture(map);
	sMap.setOrigin((float)sMap.getTextureRect().width / 2, (float)sMap.getTextureRect().height / 2);
	sMap.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	sMap.setScale(3.75, 3.75);
	sMap.setRotation(45);

	string pos = "(" + to_string(sf::Mouse::getPosition(game).x) + ", " + to_string(sf::Mouse::getPosition(game).y) + ")";

	sf::Text coords;;
	sf::Font anon;
	anon.loadFromFile("assets/fonts/AnonymousPro-Regular.ttf");
	coords.setFont(anon);
	coords.setString(pos);
	coords.setFillColor(sf::Color::White);
	coords.setCharacterSize(28);
	coords.setPosition(sf::Mouse::getPosition(game).x + 5, sf::Mouse::getPosition(game).y);

	while (game.isOpen())
	{

		string pos = "(" + to_string((sf::Mouse::getPosition(game).x - 500) / (300/radius)) + ", " + to_string((350 - sf::Mouse::getPosition(game).y) / (300/radius)) + ")";
		coords.setString(pos);
		coords.setPosition(sf::Mouse::getPosition(game).x, sf::Mouse::getPosition(game).y);

		sf::Event event;
		while (game.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed)
			{

			}

		}

		game.clear(sf::Color(50,50,50,255));
		game.draw(sMap);
		game.draw(coords);
		game.display();

	}

}

bool RadarGame(sf::RenderWindow& game)
{

	int transparentLoop = 0;
	int count = 0;
	int presses = 1;
	int trys = 5;
	int timer = 20;
	int clock = 0;
	vector<sf::CircleShape> scoreboard;

	for (int i = 0; i < trys; i++)
	{

		sf::CircleShape circle;
		circle.setRadius(25);
		circle.setFillColor(sf::Color::White);
		circle.setPosition(900, 150 + (75 * i));
		scoreboard.push_back(circle);

	}

	

	sf::Texture radar;
	radar.loadFromFile("assets/radar.png");
	sf::Sprite sRadar;
	sRadar.setTexture(radar);
	sRadar.setOrigin((float)sRadar.getTextureRect().width / 2, (float)sRadar.getTextureRect().height / 2);
	sRadar.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	sRadar.setScale(sf::Vector2f(2.75, 2.75));

	sf::Texture stick;
	stick.loadFromFile("assets/radarStick.png");
	sf::Sprite sStick;
	sStick.setTexture(stick);
	sStick.setOrigin((float)sStick.getTextureRect().width / 2, (float)128);
	sStick.setPosition((float)game.getSize().x / 2, (float)game.getSize().y / 2);
	sStick.setScale(sf::Vector2f(2.75, 2.7));

	sf::Texture blip;
	blip.loadFromFile("assets/blip.png");
	sf::Sprite sBlip;
	sBlip.setTexture(blip);
	sBlip.setOrigin((float)sBlip.getTextureRect().width / 2, (float)sBlip.getTextureRect().height / 2);
	sBlip.setPosition(((float)game.getSize().x / 2) - 128 + (rand() % 256), ((float)game.getSize().y / 2) - 128 + (rand() % 256));
	sBlip.setScale(sf::Vector2f(2.75, 2.75));

	sf::Texture clocktxt;
	clocktxt.loadFromFile("assets/timer.png");
	sf::Sprite sClock;
	sClock.setTexture(clocktxt);
	sClock.setOrigin((float)0, (float)sClock.getTextureRect().height / 2);
	sClock.setPosition(0, 94);
	sClock.setScale(sf::Vector2f(4.2, 4.2));

	sf::Text time;
	sf::Font anon;
	anon.loadFromFile("assets/fonts/AnonymousPro-Regular.ttf");
	time.setFont(anon);
	time.setString(to_string(timer));
	time.setFillColor(sf::Color::White);
	time.setCharacterSize(32);
	time.setPosition(96, 69);

	while (game.isOpen())
	{

		clock++;
		if (clock == 24)
		{
			clock = 0;
			timer--;
			time.setString(to_string(timer));
		}

		if (trys == 0 || count == 3)
			clock = 25;

		if (transparentLoop == 0)
		{
			sBlip.setColor(sf::Color(225, 255, 225, 50));
		}

		if (transparentLoop > 0 && transparentLoop < 24)
		{
			sBlip.setColor(sf::Color(225, 255, 225, 50 + (transparentLoop * 3)));
		}

		if (transparentLoop > 24 && transparentLoop < 48)
		{
			sBlip.setColor(sf::Color(225, 255, 225, 130 - (transparentLoop * 2)));
		}

		if (transparentLoop > 48) transparentLoop = 0;

		transparentLoop++;

		if (sStick.getRotation() <= 360 && trys > 0 && count < 3)
		{
			sStick.setRotation(sStick.getRotation() + (4.5 * presses));
		}
		else if (trys > 0 && count < 3)
			sStick.setRotation(0);

		sf::Event event;
		while (game.pollEvent(event))
		{

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{

					presses++;
					if(trys > 0) trys--;

					if (sBlip.getGlobalBounds().intersects(sStick.getGlobalBounds()))
					{

						int modX = 0;
						int modY = 0;

						if ((int)sStick.getRotation() / 90 == 0)
						{
							modX = 0 - 128 + (rand() % 256);
							modY = 0 - (rand() % 128);
						}

						else if ((int)sStick.getRotation() / 90 == 1)
						{
							modX = 0 - 128 + (rand() % 128);
							modY = 0 - 128 + (rand() % 256);
						}

						else if ((int)sStick.getRotation() / 90 == 2)
						{
							modX = 0 - 128 + (rand() % 256);
							modY = 0 + (rand() % 128);
						}

						else	if ((int)sStick.getRotation() / 90 == 3)
						{
							modX = 0 + (rand() % 128);
							modY = 0 - 128 + (rand() % 256);
						}

						else
						{
							modX = 0 - 128 + (rand() % 256);
							modY = 0 - 128 + (rand() % 256);
						}

						sBlip.setPosition(((float)game.getSize().x / 2) + modX, ((float)game.getSize().y / 2) + modY);
						transparentLoop = 0;
						sBlip.setColor(sf::Color(225, 255, 225, 50));

						scoreboard[scoreboard.size() - trys - 1].setFillColor(sf::Color::Green);
						count++;
					}
					else
						scoreboard[scoreboard.size() - trys - 1].setFillColor(sf::Color::Red);

				}
			}

			if (event.type == sf::Event::Resized)
			{

				sf::FloatRect newView(0.f, 0.f, event.size.width, event.size.height);
				game.setView(sf::View(newView));

			}

			if (event.type == sf::Event::Closed)
				exit(0);

		}

		game.clear(sf::Color(50,50,50,255));
		game.draw(sRadar);
		game.draw(sStick);
		game.draw(sBlip);
		game.draw(sClock);
		game.draw(time);

		for (int i = 0; i < scoreboard.size(); i++)
			game.draw(scoreboard[i]);

		game.display();

	}

}