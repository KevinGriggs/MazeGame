#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include <vector>
#include <queue>
#include "MazeGame.h"
#include "Monster.h"

//The monster class. Includes a breadth first (Djikstra's) algorithm for pathing to the player. If no path is found the monster does not move.

//Searches a node adjacent to the node at the input index given the offset
void Monster::searchAdjacentNode(int currentNodeIndex, int xOffset, int yOffset) {

	//if the adjacent node is in bounds
	if (nodeInBounds(searchedNodes[currentNodeIndex].x + xOffset, searchedNodes[currentNodeIndex].y + yOffset)) {
		//if the adjacent node is novel
		if (nodeIsNovel(searchedNodes[currentNodeIndex].x + xOffset, searchedNodes[currentNodeIndex].y + yOffset)) {

			//create a node at the adjacent coordinates and add it to searchedNodes
			Node n = Node(searchedNodes[currentNodeIndex].x + xOffset, searchedNodes[currentNodeIndex].y + yOffset, currentNodeIndex);
			searchedNodes.push_back(n);

			switch (game.getMaze()[n.y][n.x]) {
			case ' ': //if the adjacent node is traversible, add it to the queue
				searchQueue.push(searchedNodes.size() - 1);
				break;
			case 'c': //if the adjacent node is the character, set player found to true
				playerFound = true;
				break;
			case '0': //otherwise do nothing
			case 'm':
			default:
				break;
			}
		}
	}
}

//Returns true if the node at the coordinates has been searched already
bool Monster::nodeIsNovel(int x, int y) {
	for (int i = 0; i < searchedNodes.size(); i++) {
		if (searchedNodes[i].x == x && searchedNodes[i].y == y) return false;
	}
	return true;
}

//Returns true if the node at the coordinates is in the maze's bounds
bool Monster::nodeInBounds(int x, int y) {
	if (x >= 0 && x < game.getMazeWidth() && y >= 0 && y < game.getMazeHeight()) {
		return true;
	}
	return false;
}

//The monster's tick, determines the monster's best path to the player and moves them along it
//returns true if the monster caught the player
bool Monster::tick(){

	//resets the variables for the next tick
	searchedNodes.clear();
	searchQueue = queue<int>();
	playerFound = false;

	//creates a node located at the monster's position and adds it to searchedNodes and the queue
	Node monsterNode = Node(x, y);
	searchedNodes.push_back(monsterNode);
	searchQueue.push(0);

	int targetX, targetY; //The coordinates of the target node (to move the monster to)

	//While there are nodes in the queue
	while (!searchQueue.empty()) {

		int currentNodeIndex = searchQueue.front(); //get the index of the first node in the queue
		searchQueue.pop();

		//Search all 4 adjacent nodes and end the search if the player has been found
		searchAdjacentNode(currentNodeIndex, 0, -1);
		if (playerFound) break;
		searchAdjacentNode(currentNodeIndex, 0, 1);
		if (playerFound) break;
		searchAdjacentNode(currentNodeIndex, -1, 0);
		if (playerFound) break;
		searchAdjacentNode(currentNodeIndex, 1, 0);
		if (playerFound) break;
	}

	//if the player was found
	if (playerFound) {

		vector<int> path; //contains the indices of all nodes on the path

		Node &currentNode = searchedNodes.back(); //creates a reference to the final node

		//if the current node has a parent, adds the parent to the path. Repeats up the path until the monster node is reached.
		while (currentNode.parent != -1) {
			path.push_back(currentNode.parent);
			currentNode = searchedNodes[currentNode.parent];
		}

		//if the player has not been reached moves the monster two tiles forward along the path
		if (path.size() >= 3) {
			targetX = searchedNodes[path[path.size() - 3]].x;
			targetY = searchedNodes[path[path.size() - 3]].y;
			game.moveMonster(x, y, targetX, targetY); //moves the monster on the maze
			x = targetX;
			y = targetY;
		}
		else {//if the player has been reached moves the monster to the player for display purposes, resets the variables, and returns true
			targetX = game.getPlayerX();
			targetY = game.getPlayerY();
			game.moveMonster(x, y, targetX, targetY);
			x = targetX;
			y = targetY;

			return true;
		}
	}

		return false; //if the player was not found
}