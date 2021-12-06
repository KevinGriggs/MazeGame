#pragma once

//The loader class. Loads the maze from the text file indicated by the player's input in the menu.

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include <vector>
#include "MazeGame.h"
#include "MazeLoader.h"
#include "Monster.h"

using namespace std;

//inputs the maze and check's it's format, returns 0 if maze was loaded and -1 if load failed 
int MazeLoader::inputMaze(string name) {

	mazeInput = ifstream(); //resets the stream

	mazeInput.open(name);

	//if the file fails to open, informs the player and returns -1, allowing main to repeat input
	if (mazeInput.fail())
	{
		cout << "\nMaze " << name << " couldn't be found. Please try again.\n\n";
		return -1;
	}

	vector<vector<char>> &maze = game.getMaze(); //gets a reference to the maze

	mazeInput >> mazeWidth; //gets the maze's width from the file
	//checks if the maze is the right format, if not informs the player and returns -1, allowing main to repeat input
	if (mazeInput.fail()) { 
		cout << "\nMaze " << name << " is an invalid format, please load another maze.\n\n";
		return -1;
	}

	game.setMazeWidth(mazeWidth); //sets the maze's width in the game
	
	//gets the maze's height from the file
	mazeInput >> mazeHeight;
	
	//checks if the maze is the right format, if not informs the player and returns -1, allowing main to repeat input
	if (mazeInput.fail()) {
		cout << "\nMaze " << name << " is an invalid format, please load another maze.\n\n";
		return -1;
	}

	game.setMazeHeight(mazeHeight); //sets the maze's height in the game
	
	game.getMaze().resize(mazeHeight); //resizes the maze's height

	//resizes the maze's width per level
	for (int i = 0; i < mazeHeight; i++) {
			maze[i].resize(mazeWidth);
		}
	
	//checks if the maze is the right format, if not informs the player and returns -1, allowing main to repeat input
	if (mazeInput.get() != '\n') {
		cout << "\nMaze " << name << " is an invalid format, please load another maze.\n\n";
		return -1;
	}
	

	//iterates through the file, starting on the first row, first column, then moving left to right, up to down
	for (int y = 0; y < mazeHeight; y++)
	{
		for (int x = 0; x < mazeWidth; x++)
		{
			mazeInput.get(maze[y][x]); //inputs the next character
			//get's the player's intial position and sets that in the game
			if (maze[y][x] == 'c')
			{
				game.setPlayerX(x);
				game.setPlayerY(y);
			}
			else if (maze[y][x] == 'm') //gets the monster's initial position and sets that in the game
			{
				game.addMonster(x,y);
			}

			//if the maze contains a wrong character informs the player and returns -1, allowing main to repeat input 
			else if (maze[y][x] != ' ' && maze[y][x] != 'e' && maze[y][x] != '0') {
				cout << "\nMaze " << name << " is an invalid format, please load another maze.\n\n";
				return -1;
			}
		}

		mazeInput.get(); //skips the new line character at the end of every line
	}

	mazeInput.close();
	return 0; //if the maze was successfully loaded returns 0
}