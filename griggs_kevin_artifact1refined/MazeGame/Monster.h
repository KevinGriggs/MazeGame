#pragma once

//The monster class. Includes a breadth first (Djikstra's) algorithm for pathing to the player. If no path is found the monster does not move.

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include <vector>
#include <queue>

using namespace std;

//used to solve issue with circular dependency, see here for fix https://stackoverflow.com/questions/23283080/compiler-error-c4430-missing-type-specifier-int-assumed
class MazeGame;


class Monster {

	//Node for pathfinding.
	struct Node {
		//The node coordinated
		int x;
		int y;

		//The index of the node's parend in searchedNodes
		int parent = -1;

		Node() {};
		Node(int inX, int inY) : x{ inX }, y{ inY }{}; //constructor for first node
		Node(int inX, int inY, int inParent) : x{ inX }, y{ inY }, parent{ inParent }{}; //constructor for subsequent nodes
	};

	//The monster's coordinates
	int x;
	int y;

	bool playerFound = false; //whether or not the player has been found

	MazeGame &game; //A reference to the game

	queue<int> searchQueue; //a queue containing node indices for searching

	vector<Node> searchedNodes; //a container for all searched and queued nodes

	public:

		//Neccessary constructor. sets the game reference
		Monster(int inX, int inY, MazeGame &inGame) : x{ inX }, y{ inY }, game{ inGame }{}

		//The monster's tick, determines the monster's best path to the player and moves them along it
		//returns true if the monster caught the player
		bool tick();

	private:
		
		//Returns true if the node at the coordinates has been searched already
		bool nodeIsNovel(int x, int y);

		//Returns true if the node at the coordinates is in the maze's bounds
		bool nodeInBounds(int x, int y);

		//Searches a node adjacent to the node at the input index given the offset
		void searchAdjacentNode(int currentNodeIndex, int xOffset, int yOffset);

};
