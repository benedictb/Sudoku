/*
Benedict Becker
bbecker5
lab5
*/
#ifndef SUDOKU
#define SUDOKU

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Puzzle.cpp"
using namespace std;

class Sudoku{
public:
	Sudoku(string filename); //constructor that takes in the name of a file
	~Sudoku();
	void play(); //play the game
	int getQuad(int r, int c); //get the "quadrant" of two coordinates
	int checkQuad(int quad, int input); //see if a number is in a "quadrant"
	int validPlacement(int r,int c, int input); //see if the input is a valid placement
	int gamecheck(); //check to see if the game is over
	int checkRow(int r,int input); //check to see if the input is valid in this row
	int checkCol(int c, int input); //check to see if the input is valid in this column
	int input();//input a number, row and column
	int isMovable(int r, int c); //is this placement allowed to change?


	//these are the new functions for solving soduku
	void updateSolData(); //update the 3d vector
	void uniqueFiller(); //fill in the single possibility cells
	int numOfOnes(vector<int> vect); //return the number of 1's in a vector
	int findTheOne(vector<int> vect); //return the first index with a 1 in the vector
	void SingletonCol(int col); //does singleton for a col
	void SingletonRow(int row); //same for a row
	void SingletonGrid(int grid); //same for a minigrid
	void solver(); //incorporates all of these functions to solve the puzzle


private:
	Puzzle<int> puz; //puzzle board
	Puzzle<int> constPuz; //backup puzzle for checking changability
	vector< vector< vector<int> > > solData; //holds data necessary for solving the puzzle
	//solData is a 9X9X10 matrix that holds the actual board in the 0th index of the third dimension, and the possibilities of each 
	//cell in the remaining 9 cells
};

#endif

