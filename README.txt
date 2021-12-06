Author: Kevin Griggs
Written in C++

This program starts a maze that the user must traverse using commands.

The maze design is input from a file into an array, with 0s to denote walls and spaces to denote traversable space.
The first line of the file is always the dimensions of the maze, width then height, separated by a space.
The start is denoted by 'c' (for the character), and the end is denoted by 'e'.
Empty space within the dimensions of the maze must be spaces.

The user types in w, s, a, or d to control the character, denoted as c
Every turn the monsters, denoted by 'm' if there is one, moves 2 steps along the best path to the character. 
If the monster catches the character, the player loses.

The method used for the monster's AI is inspired by Dijkstra's Algorithm as is explained here:
http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html

This program was written as my final project for a C++ course at the Community College of Vermont three years ago.
It has since been refined for the purposes of my Game Programming Capstone at Southern New Hampshire University and publication in my portfolio
