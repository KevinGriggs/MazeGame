#pragma once

// The menu class. Prints the main menu and retrieves maze selection from the user.
//Also prompts the user whether or not they want to continue after completing a maze.

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include "MazeGame.h"

using namespace std;

class Menu {
	
	public:
		//Launches the main menu that prompt the user for their selection of maze. Returns the maze file name.
		string launchMenu();
		
		// Prints the ending message
		//and prompts the user whether or not they wish to continue and play another maze
		//takes the games result as an input and returns whether or not to play again
		bool printEndingPromptContinue(int result);
};
