

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include "MazeGame.h"
#include "Monster.h"

using namespace std;

//Moves the monster at the original position to the new position
void MazeGame:: moveMonster(int originalX, int originalY, int newMonsterX, int newMonsterY) {
	maze[newMonsterY][newMonsterX] = 'm'; //sets the character at the new position to the monster
	maze[originalY][originalX] = ' '; //sets the character at the old position to an empty space
}

//Adds the monster at the specified position (called by the loader)
void MazeGame::addMonster(int monsterX, int monsterY) {
	//creates a new monster with a reference to this game object and adds it to the monsters list 
	monsters.push_back(Monster(monsterX, monsterY, *this));
}


//gets and handles the input and moves the player if appropriate, returns 1 if the game was won, 0 if the character moved,
		//-1 if the player lost, and -2 if the player wants to quit
int MazeGame::handleInput()
{
	string input = ""; //holds the input string

	cout << "\nWhich way would you like to go? (up: w, down: s, left: a, right: d, quit: quit)\n";

	cin >> input;

	while (input != "w" && input != "s" && input != "a" && input != "d" && input != "quit") //checks for valid input and prompts the user if incorrect
	{
		cout << "\nThat is not a valid direction, please try again.\n";
		cin >> input;
	}

	int targetTileX = playerX, targetTileY = playerY; //stores the coordinates of the intended tile to travel to

	if (input == "w") //sets target tile coordinates and exits the game if the player prompts
		targetTileY--;
	else if (input == "s")
		targetTileY++;
	else if (input == "a")
		targetTileX--;
	else if (input == "d")
		targetTileX++;
	else
		return -2; //if the player wants to quit, return -2

	//determines win/loss or moves the character depending on the content of the target tile
	if (targetTileX >= 0 && targetTileX < mazeWidth && targetTileY >= 0 && targetTileY < mazeHeight) //checks to make sure tile isn't out of bounds
	{
		if (maze[targetTileY][targetTileX] == 'e') //checks if the tile is the end
			return 1; //game has been won	

		else if (maze[targetTileY][targetTileX] == ' ') //checks if the tile is traversable
		{
			maze[targetTileY][targetTileX] = 'c'; //moves the character icon to the intended tile
			maze[playerY][playerX] = ' '; //changes the character's previous position to an empty space
			playerX = targetTileX; //updates player coordinates
			playerY = targetTileY;
			return  0;
		}
		else if (maze[targetTileY][targetTileX] == 'm') {
			return -1; //the player walked into the monster, has lost
		}
	}
}

//prints the maze to the screen
void MazeGame::printMaze()
{
	system("cls"); //clears the screen for reprinting

	for (int y = 0; y < mazeHeight; y++) //iterates horizontally then vertically copying the maze to the screen
	{
		for (int x = 0; x < mazeWidth; x++)
		{
			cout << maze[y][x];
		}

		cout << endl;
	}

	return;
}

//Starts the game loop, returns 1 if the player won, -1 if the player lost, and 0 if the player quit
int MazeGame::play()
{
	while (!(hasWon || hasLost)) //game loop
	{
		printMaze(); //print the maze

		//prompt and handle input
		switch (handleInput()) {
			case 1: //player reached exit
				return 1; //end with victory
			case -1: //player walked into the monster
				return -1; //end with loss 
			case -2: //player quit
				system("cls"); //clears the screen for reprinting
				return 0; //end and close program
			default: //player entered empty space
				break; //continue to monster turn
		}

		for (int i = 0; i < monsters.size(); i++){ //for each monster
			hasLost = monsters[i].tick(); //ticks the monster
			if (hasLost) return -1; //end with loss if the monster caught the player
		}
	}
}
