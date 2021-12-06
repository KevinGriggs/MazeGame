//Author: Kevin Griggs
//This program starts a maze that the user must traverse using commands.
//The maze design is input from a file into an array, with 0s to denote walls and spaces to denote traversable space.
//The first line of the file is always the dimensions of the maze, width and height, separated by a space.
//The start is denoted by 'c' (for the character), and the end is denoted by 'e'.
//The user types in w, s, a, or d to control the character, denoted as c
//Every turn the monsters, denoted by 'm' if there is one, moves 2 steps along the best path to the character. 
//If the monster catches the character, the player loses.
//The method used for the monster's AI is (or was at least inspired by) Dijkstra's Algorithm as is explained here:
//http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html

//This program was written as my final project for a C++ course at the Community College of Vermont three years ago.
//It has since been refined for the purposes of my Game Programming Capstone at Southern New Hampshire University and publication in my portfolio

//This is the entry point for the program

#pragma once
#include "MazeGame.h"
#include "Menu.h"
#include "MazeLoader.h"
#include <string>

//The entry
int main() {

	string mazeName; //the maze's file name
	
	Menu menu = Menu(); //the menu object
	MazeGame game = MazeGame(); //the game object, reset on new games
	MazeLoader loader = MazeLoader(game); //the loader object, reads maze files and loads them into the game
	
	int result; //the results of the game -1 for loss, 1 for win, 0 for quit
	bool playAgain = false; //holds whether or not to start a new maze

	//repeat while player wishes to play another maze
	do {
		game = MazeGame();//resets the game;

		//repeat if unable to open maze
		do {
			mazeName = menu.launchMenu(); //launches the menu
			if (mazeName == "quit") return 1; //quit if prompted on maze load
		} while (loader.inputMaze(mazeName) == -1);

		result = game.play(); //play the game and store the results

		if (result != 0) playAgain = menu.printEndingPromptContinue(result); //get whether or not to start another maze from a prompt

	} while (playAgain);

	return 1; //end if player does not want to continue
}