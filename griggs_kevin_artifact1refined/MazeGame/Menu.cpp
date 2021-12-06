/* The game's main menu */

#pragma once

#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include <String>
#include "MazeGame.h"
#include "Menu.h"

using namespace std;

//Launches the main menu that prompt the user for their selection of maze. Returns the maze file name.
string Menu::launchMenu() {

	string mazeName; //holds the maze's file name

	cout << "Please enter the file name of the maze that you would like to play (type \"quit\" to quit):\n";
	cin >> mazeName;

	//if the player doesn't want to quit adds .txt to input names that lack the file extention
	if (mazeName != "quit") {
		if (mazeName.find(".txt") == string::npos) mazeName = mazeName + ".txt"; //if supplied name lacks file extention, adds it;
	}

	return mazeName;
}


// Prints the ending message
//and prompts the user whether or not they wish to continue and play another maze
//takes the games result as an input and returns whether or not to play again
bool Menu::printEndingPromptContinue(int result) {

	//if the player lost print the lose message, if they won print the win message
	if(result == -1) cout << "\nYou were eaten by the monster\n\n";
	else cout << "\nYou Won!\n\n";

	string playAgain; //holds the player's input for whether or not to play again

	//prompts the user whether or not to play again and gets input
	cout << "Would you like to play another maze? y/n:\n";
	cin >> playAgain;

	//with the input is invalid, repeat prompt and input
	while (playAgain != "y" && playAgain != "n") {
		cout << "Invalid input, please try again.\n\n";
		cout << "Would you like to play another maze? y/n:\n";
		cin >> playAgain;
	}

	//if the player wants to play again, clear the screen in preparation for the next game and return true, otherwise return false
	if (playAgain == "y") {
		system("cls");
		return true;
	}
	else if (playAgain == "n") {
		return false;
	}

}