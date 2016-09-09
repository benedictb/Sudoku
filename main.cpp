/*
Benedict Becker
bbecker5
lab5
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include "Puzzle.cpp"
#include "Sudoku.h"
using namespace std;

int main(void){

	string filename;
	char choice;

	system("clear");
	system("ls puzzles | grep .txt"); //display the txts in the folder

	cout << endl << "During the game, input -1 to quit";
	cout <<endl<< "Filename? "; 
	cin >> filename;

	filename = string("puzzles/") + filename;

	Sudoku puz(filename); //instantiate a puzzle int

	cout << "Would you like to play or solve? Enter p or s." << endl;
	cin >> choice;
	
	if (choice == 'p'){
		puz.play(); //play the game
	} else if (choice == 's'){
		puz.solver(); //solve the puzzle
	}


}
