#pragma once

//The game class. Contains and outputs the maze, handles character placement and movement/player input, contains the monster objects, and
//tracks the game's state.

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include <vector>
#include "Monster.h"

using namespace std;

class MazeGame {
	
	bool hasWon = false; //indicates if the user has won
	bool hasLost = false; //indicates if the user has lost;

	int playerX, playerY; //the player coordinates
	
	int mazeHeight, mazeWidth; //The maze dimensions

	vector<vector<char>> maze; //holds maze data
	vector<Monster> monsters; //holds the monster objects

	public:

		//Setters
		void setPlayerX(int x) { playerX = x; }
		void setPlayerY(int y) { playerY = y; }
		void setMazeHeight(int h) { mazeHeight = h; }
		void setMazeWidth(int w) { mazeWidth = w; }

		//Getters
		int getMazeHeight() { return mazeHeight; }
		int getMazeWidth() { return mazeWidth; }
		int getPlayerX() { return playerX; }
		int getPlayerY() { return playerY; }

		//Adds the monster at the specified position (called by the loader)
		void addMonster(int monsterX, int monsterY);

		//Moves the monster at the original position to the new position
		void moveMonster(int originalX, int originalY, int newMonsterX, int newMonsterY);

		//Returns a reference to the maze
		vector<vector<char>> &getMaze() { return maze; }
		
		//Starts the game loop, returns 1 if the player won, -1 if the player lost, and 0 if the player quit
		int play();

		//Prints the maze
		void printMaze();

		//gets and handles the input and moves the player if appropriate, returns 1 if the game was won, 0 if the character moved,
		//-1 if the player lost, and -2 if the player wants to quit
		int handleInput();

};