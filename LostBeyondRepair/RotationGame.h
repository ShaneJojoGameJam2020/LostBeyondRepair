#pragma once
#include "MiniGame.h"
#include <queue>
#include <set>
#include <utility>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

struct RotationGameBoard {
	class Node {
	public:
		std::vector<bool> connections;
		std::vector<Node *> neighbors;
		std::string name = "";
		Node() {
			for (int i = 0; i < 4; i++) {
				connections.push_back(rand() % 2);
			}
			while (true) {
				int count = 0;
				for (int i = 0; i < 4; i++) {
					if (connections[i] == true) {
						count++;
					}
				}
				if (count > 1) {
					break;
				}
				for (int i = 0; i < 4; i++) {
					if (rand() % 3 == 0) {
						connections[i] = true;
					}
				}
			}
		}
		void RotateLeft() {
			for (int i = 0; i < 4; i++) {
				bool oldValue = connections[i];
				connections[i] = connections[(i + 3) % 4];
				connections[(i + 3) % 4] = oldValue;
			}
		};
		void RotateRight() {
			for (int i = 0; i < 4; i++) {
				bool oldValue = connections[i];
				connections[i] = connections[(i + 1) % 4];
				connections[(i + 1) % 4] = oldValue;
			}
		}
		void addNeighbor(Node * newNeigbor) {
			neighbors.push_back(newNeigbor);
		}

		bool enterableFrom(int direction) {
			return connections[(direction + 2) % 4];
		}

		std::string getString() {
			if (name != "") {
				return name;
			}
			int count = 0;
			for (int i = 0; i < 4; i++) {
				if (connections[i] == true) {
					count++;
				}
			}
			if (count == 4) {
				name = "Cross";
				return name;
			}
			if (count == 3) {
				name = "Tee";
				return name;
			}
			if (count == 2) {
				if (connections[0] == connections[2]) {
					name = "Angle";
					return name;
				}
				else {
					name = "Line";
					return name;
				}
			}
		}

		int getRotation() {
			if (getString() == "Cross") {
				return 0;
			}
			else if (getString() == "Tee") {
				for (int i = 0; i < 4; i++) {
					if (connections[i] == false) {
						return (i  + 2) % 4;
					}
				}
			}
			else if (getString() == "Line") {
				if (connections[0] == true) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else if (getString() == "Angle") {
				for (int i = 0; i < 4; i++) {
					if (connections[i] == true && connections[(i + 1) % 4] == true) {
						return i;
					}
				}
			}
		}
	};
	Node * start;
	Node * goal;
	std::vector<std::vector<Node>> nodes;
	int size = 3;
	bool AreNodesConnected(int i1,int  j1, int i2, int j2) {
		if ((abs(i1 - i2) > 1 || abs(j1 - j2)  > 1)  || (abs(i1-i2) == abs(j1 = j2))){
			return false;
		}
		
		Node * node1 = &nodes[i1][j1];
		Node * node2 = &nodes[i2][j2];
	
		return true;
	}

	RotationGameBoard() {
		for (int i = 0; i < size; i++) {
			std::vector<Node> row(size);
			
			nodes.push_back(row);
			if (i == 0) {
				start = &nodes[0][0];
			}
			if (i == size - 1) {
				goal = &nodes[i][i];
			}
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((i - 1) >=0) {
					nodes[i][j].addNeighbor(&nodes[i - 1][j ]);
				}
				else {
					nodes[i][j].addNeighbor(NULL);
				}
				if (j + 1 < size) {
					nodes[i][j].addNeighbor(&nodes[i][j + 1]);
				}
				else {
					nodes[i][j].addNeighbor(NULL);
				}
				if ((i + 1 ) < size) {
					nodes[i][j].addNeighbor(&nodes[i + 1][j]);
				}
				else {
					nodes[i][j].addNeighbor(NULL);
				}
			
				if ((j - 1 >= 0)) {
					nodes[i][j].addNeighbor(&nodes[i][j - 1]);
				}
				else {
					nodes[i][j].addNeighbor(NULL);
				}
			}
		}
	}
	bool checkComplete() {
		std::queue<Node *> q;
		std::set<Node *> vistiedNodes;
		q.push(start);
		vistiedNodes.insert(start);
		while (!q.empty()) {
			Node * curNode = q.front();
			if (curNode == goal) {
				return true;
			}
			for (int i = 0; i < curNode->neighbors.size(); i++) {
				if (curNode->connections[i] && (curNode->neighbors[i] != NULL)) {
					if (curNode->neighbors[i]->enterableFrom(i)) {
						if (vistiedNodes.count(curNode->neighbors[i]) == 0) {
							vistiedNodes.insert(curNode  -> neighbors[i]);
							q.push(curNode->neighbors[i]);
						}
					}
				}
			}
			q.pop();
		}
		return false;
	}
	void makePossible() {
		Node * curNode = start;
		while (curNode != goal) {
			int index = 1 + (rand() % 2);
			if (curNode->neighbors[index] == NULL) {
				if (index == 1) {
					index = 2;
				}
				else {
					index = 1;
				}
			}
			curNode->connections[index] = true;
			curNode->neighbors[index]->connections[(index + 2) % 4] = true;
			curNode = curNode->neighbors[index];
		}
	}
	void scramble(int numRots) {
		while (numRots != 0) {
			int i = rand() % size;
			int j = rand() % size;
			nodes[i][j].RotateRight();
			numRots--;
		}
	}
	void takeTurn(int i, int j) {
		nodes[i][j].RotateLeft();
	}
};

struct RotationGame : public MiniGame {
	bool play(sf::RenderWindow& game);
};