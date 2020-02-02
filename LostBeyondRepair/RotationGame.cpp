#pragma once
#include "RotationGame.h"
#include "MiniGame.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string.h>
using namespace std;

bool RotationGame::play(sf::RenderWindow& game)
{

	sf::Texture textL;
	textL.loadFromFile("assets/pipeL.png");

	sf::Texture textStraight;
	textStraight.loadFromFile("assets/pipeLine.png");

	sf::Texture textCross;
	textCross.loadFromFile("assets/pipeCross.png");

	sf::Texture textT;
	textT.loadFromFile("assets/pipeT.png");

	vector<sf::Sprite> nodeSprites;
	vector<RotationGameBoard::Node> nodeLocations;

	RotationGameBoard board;

	if (board.checkComplete() == false)
		board.makePossible();

	for (int i = 0; i < board.nodes.size(); i++)
	{

		for (int j = 0; j < board.nodes[i].size(); j++)
		{

			sf::Sprite newSprite;

			if (board.nodes[i][j].getString() == "Line")
				newSprite.setTexture(textStraight);
			
			if (board.nodes[i][j].getString() == "Cross")
				newSprite.setTexture(textCross);

			if (board.nodes[i][j].getString() == "Tee")
				newSprite.setTexture(textT);

			if (board.nodes[i][j].getString() == "Angle")
				newSprite.setTexture(textL);

			newSprite.setOrigin((float)newSprite.getTextureRect().width / 2, (float)newSprite.getTextureRect().height / 2);
			newSprite.setPosition(200 + 80*i,200 + 80*j);
			newSprite.setRotation(90 * board.nodes[i][j].getRotation());
			newSprite.setScale(10, 10);

			nodeSprites.push_back(newSprite);
			nodeLocations.push_back(board.nodes[i][j]);

		}

	}

	while (game.isOpen())
	{

		sf::Event event;
		while (game.pollEvent(event))
		{

			if(event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
				{

					for (int i = 0; i < nodeSprites.size(); i++)
					{

						if (nodeSprites[i].getGlobalBounds().contains(game.mapPixelToCoords(sf::Mouse::getPosition(game))))
						{

							nodeLocations[i].RotateLeft();
							nodeSprites[i].setRotation(nodeSprites[i].getRotation() - 90);

							bool test = board.checkComplete();
							if (test) cout << "ITS GOOD!" << endl;

						}

					}

				}

		}

		game.clear(sf::Color::Black);

		for (int i = 0; i < nodeSprites.size(); i++)
		{
			game.draw(nodeSprites[i]);
		}

		game.display();



	}
	return true;
}