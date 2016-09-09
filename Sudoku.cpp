/*
Benedict Becker
bbecker5
lab5
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include "Sudoku.h"
using namespace std;

Sudoku::Sudoku(string filename) : puz(9,filename), constPuz(9,filename){

	vector<vector <int> > vect;
	vector<int> intVect;

	for(int i=0;i<9;i++){ //insert vectors for the columns
		solData.push_back(vect);
		for (int j=0;j<9;j++){
			solData[i].push_back(intVect); //insert vectors for the data
			solData[i][j].push_back((*puz.getBoard())[i][j]); //initialize the actual "solution" to be what is currently on the board
			for (int k=1;k<10;k++){//set data to 0
				solData[i][j].push_back(0);
			}
		}
	}
}

Sudoku::~Sudoku(){}

void Sudoku::play(){
	while (1){  
	//display the board, take in input, and then see if the game is over
		
		puz.display();

		if (input()){return;}
		if (gamecheck()) {return;}

	}
}

int Sudoku::getQuad(int r, int c){
	int val = 0; 
	/*returns the "coordinates" of the top left corner of the minigrid that the
	(r,c) pair is in. Is extracted using r = val/10 and c = val%10
	*/

	if (r<3){
		val+=0;
	} else if(r<6){
		val+=30;
	} else if (r<9){
		val+=60;
	} else { return -1;}

	if (c<3){
		val+=0;
	} else if(c<6){
		val+=3;
	} else if (c<9){
		val+=6;
	} else { return -1;}

	return val;
}

int Sudoku::checkQuad(int quad, int input){

	int r = quad/10; //extract the coordinates from the quad number
	int c= quad%10;


	for(int i=0;i<3;i++){ //looping through all 9 points, see if the input is already in the minigrid
		for (int j=0;j<3;j++){
			if((*puz.getBoard())[r+i][c+j] == (input)){return 0;} //checks the coordinate against the input
		}
	}

	return 1; //if no matches, return true
}

int Sudoku::checkCol(int c, int input){ //checks to see if the input number is already in the column
	for (int i=0;i<9;i++){ 
		if ((*puz.getBoard())[i][c] == input) {return 0;}
	}
	return 1;
}

int Sudoku::checkRow(int r, int input){ //checks to see if the input number is in the row
	for (int i=0;i<9;i++){
		if ((*puz.getBoard())[r][i] == input) {return 0;}
	}
	return 1;
}

int Sudoku::validPlacement(int r,int c, int input){ //checks the three constraints for a given (r,c) pair and input

	if (!(checkQuad(getQuad(r,c),input))) {return 0;} //gets the quad and checks the quad in the same call
	if (!(checkCol(c,input))) {return 0;}
	if (!(checkRow(r,input))) {return 0;}

	return 1;
}

int Sudoku::gamecheck(){
	for(int i=0;i<9;i++){
		for (int j=0;j<9;j++){
			if ((*puz.getBoard())[i][j] == 0) //because of the detailed validPlacement function, if there is no 0's left, then the game has been won
				return 0;
		}
	}
	cout << endl << "Congrats! You solved the puzzle!" << endl;
	return 1; //return true to exit the program
}

int Sudoku::input(){ 
	int r,c,input, movable=0;

	puz.display();

	while(movable==0){ //needs to be "changable" spot, blank in the original puzzle

		cout << "Please pick a row: "; 
	cin >> r;
		r--; //for array numbering
		while ((r < 0) || (r>8)){ //has to be in bounds or else seg fault
			cout<< endl<< "Please chooose a valid entry: ";
			cin >> r;
			r--;
		} 

		puz.display(); //same as row
		cout << "Please pick a column: ";
		cin >> c;
		c--;
		while ((c < 0) || (c>8)){
			cout<< endl<< "Please chooose a valid entry: ";
			cin >> c;
			c--;
		} 

		puz.display();
		if (isMovable(r,c)){ //checks to see if it is a movable value, if it is, then the loop is exited
			movable =1;
		} else {
			cout << endl<< "Sorry, this was part of the original puzzle and cannot be changed" << endl;
		}
	}


	puz.display();
	cout << "Please pick your number: ";
	cin >> input;
	if (input==-1) {return 1;} //-1 exits the program
	while ((input < -1) || (input>9) || !(validPlacement(r,c,input))) { //needs to be a valid input, checked by the validPlacement function
		cout<< endl<< "Please chooose a valid entry: ";
		cin >> input;
		if (input==-1) {return 1;}
	} 

	(*puz.getBoard())[r][c] = input;
	return 0; //everything worked out fine is 0 in this case
}

int Sudoku::isMovable(int r, int c){ //checks to see if the coordinates are changeable by referencing the backup copy of the puzzle
	if ((*constPuz.getBoard())[r][c] == 0){
		return 1;
	}
	return 0;
}


//The implementation for the solver is below

void Sudoku::updateSolData(){ 
	//this updates the possible positions for each unfilled slot. This gets called before all of the algorithms to make sure
	//that they dont write over each other or write the wrong data

	for(int i=0;i<9;i++){ //looping through all 9 points, see if the input is already in the minigrid
		for (int j=0;j<9;j++){
			if (solData[i][j][0]==0){ //if it is unfilled, update the data
				for (int k=1;k<10;k++){
					if (validPlacement(i,j,k)){ //if the number can be placed here, make it a 1, otherwise make it a zero
						solData[i][j][k]=1; 
					} else {
						solData[i][j][k]=0; //this refreshes the data
					}
				}
			}
		}
	}
}

void Sudoku::uniqueFiller(){ //if there is only one possibility for a square, place that one possibility.

	for(int i=0;i<9;i++){ //looping through all 9 points, see if the input is already in the minigrid
		for (int j=0;j<9;j++){
			if (solData[i][j][0]==0 && numOfOnes(solData[i][j])==1){  

				//I update both of these because different functions use both. 
				solData[i][j][0]=findTheOne(solData[i][j]); //update the soldata
				(*puz.getBoard())[i][j] = findTheOne(solData[i][j]); //update the real board
			}
		}
	}
}

int Sudoku::numOfOnes(vector<int> vect){ //finds the number of 1's in a vector, returns that number
	int s=0;
	for (int i=1;i<10;i++){
		if (vect[i]==1){s++;}
	}
	return s;
}

int Sudoku::findTheOne(vector<int> vect){ //returns the first index of the vector that has a 1 (besides 0).
	for (int i=1;i<10;i++){
		if (vect[i]==1){return i;}
	}
	return -1; //returns -1 if none were found
}

void Sudoku::SingletonCol(int col){ 
	int possibleArr[10]={0}; //initialize the data array to 0's. size 10 so that things match up
	for (int row=0;row<9;row++){ //go through rows
		if (solData[row][col][0]==0){ //if cell is zero, record possibilities into possibleArr
			for (int val=1;val<10;val++){
				if (solData[row][col][val]==1) { 
					possibleArr[val]++;
				}
			}
		}
	}

	for (int val=1;val<10;val++){ //for all the possible vals in possibleArr
		if(possibleArr[val]==1){ //if there is only one place to put that number
			for(int row=0; row<9;row++){ //find the cell
				if(solData[row][col][val]==1 && (solData[row][col][0]==0)){
					solData[row][col][0]=val; //and put it into the cell
					(*puz.getBoard())[row][col] = val;
					updateSolData(); //very important to update solData each time I found out. Keeps things current
					break; //leave (just to save a little computing)
				}
			}
		}
	}
}

void Sudoku::SingletonRow(int row){ //basically the same implimentation as column, but with a row
	int possibleArr[10]={0};
	
	for (int col=0;col<9;col++){
		if (solData[row][col][0]==0){
			for (int val=1;val<10;val++){
				if (solData[row][col][val]==1){
					possibleArr[val]++;
				}
			}
		}
	}

	for (int val=1;val<10;val++){
		if(possibleArr[val]==1){
			for(int col=0; col<9; col++){
				if(solData[row][col][val]==1 && (solData[row][col][0]==0)){
					solData[row][col][0]=val;
					(*puz.getBoard())[row][col] = val;
					updateSolData();
					break;
				}
			}
		}
	}
}

void Sudoku::SingletonGrid(int grid){ //similar to row and col singleton, but in this case there is another for loop because the section
	//being looped through is 2d instead of 1d
	int possibleArr[10]={0};
	int row = grid/10;
	int col=grid%10;
	for (int r=0;r<3;r++){
		for (int c=0; c<3;c++){
			if (solData[row+r][col+c][0]==0){ //starting coordinates + the offset
				for (int val=1;val<10;val++){
					if (solData[row+r][col+c][val]==1){
						possibleArr[val]++;
					}
				}
			}
		}
	}

	for (int val=1;val<10;val++){
		if (possibleArr[val]==1){
			for (int r=0;r<3;r++){
				for (int c=0;c<3;c++){
					if (solData[row+r][col+c][val]==1 && (solData[row+r][col+c][0]==0)){
						solData[row+r][col+c][0]=val;
						(*puz.getBoard())[row+r][col+c] = val;
						updateSolData();
						break;
					}
				}
			}
		}
	}
}

void Sudoku::solver(){

	int gridIDs[9] = {0,3,6,30,33,36,60,63,66}; //possible grid numbers. See getQuad and checkQuad for more info

	int counter=0; //bonus feature that counts number of turns needed to solve the puzzle

	puz.display(); //displays it initially

	updateSolData(); //load the data


	while (gamecheck()==0){ //while the puzzle hasn't been solved...keep working

		uniqueFiller();  //first fill up with the unique numbers
		updateSolData(); 
		
		for (int i=0;i<9;i++){ //run singleton through all the columns
			SingletonCol(i);
		}
		
		for (int i=0;i<9;i++){ //run singleton through all the rows
			SingletonRow(i);
		}

		for (int i=0;i<9;i++){ //blah blah all the minigrids
			SingletonGrid(gridIDs[i]);
		}


		counter++; //counts each loop

		usleep(750000); //pause: so it looks the computer is working hard solving this (it's not) 
		puz.display(); //display this round 




	}

	puz.display(); //display the final puzzle and print the number of rounds it took to solve
	cout << "It took " << counter << " rounds to solve this one." << endl;

	return;

}