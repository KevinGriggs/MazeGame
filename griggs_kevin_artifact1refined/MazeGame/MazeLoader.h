//The loader class. Loads the maze from the text file indicated by the player's input in the menu.

#pragma once
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include <vector>
#include "MazeGame.h"

class MazeLoader {
	ifstream mazeInput; //input stream for the file
	int mazeHeight, mazeWidth; //the maze's height and width, input from the file and used for further input
	MazeGame &game; //a reference to the game object for setting values and importing the maze

	public:
		MazeLoader(MazeGame &inGame) : game{ inGame } {} //neccessary constructor, sets the game reference

		int inputMaze(string name); //inputs the maze and check's it's format, returns 0 if maze was loaded and -1 if load failed 
};