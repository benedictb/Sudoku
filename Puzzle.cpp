/*
Benedict Becker
bbecker5
lab5
*/
#ifndef PUZZLE
#define PUZZLE

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

template <typename T>
class Puzzle{
public:

	Puzzle(int, string);
	~Puzzle();
	void display();
	int getSize();
	vector< vector<T> >* getBoard(); //returns a pointer to the board, needed for the sudoku game class

private:
  vector< vector<T> > board;
  int size; //useful for the display function
};

template <typename T>
vector< vector<T> >* Puzzle<T>::getBoard(){
	return &board;
}

template <typename T>
int Puzzle<T>::getSize(){
	return size;
}



template <typename T>
Puzzle<T>::Puzzle(int boardSize, string filename){

	size = boardSize;
	T temp;

	for(int i=0; i<size;i++){ //put in size size-sized vectors (sorry)
		board.push_back(vector<T>(size));
	}

	ifstream dataFile (filename.c_str()); //need the filename to be a c_str for it to work

	for (int i=0; i<size; i++){ //read in the data
		for (int j=0; j<size; j++){
			dataFile >> temp;
			board[i][j] = temp;
		}
	}
	dataFile.close();
}

template <typename T>
Puzzle<T>::~Puzzle(){}


template <typename T>
void Puzzle<T>::display(){ //this is mostly just formatting it to have the index and grid
	system("clear");
	for (int i=0;i<size;i++){
		cout << "(" << i + 1 << ")| ";
		for (int j=0;j<size;j++){
			if (board[i][j] == 0 || board[i][j] == '0' ){
				cout << " ";
			} else {
				cout << board[i][j];
			}
			cout << " ";
			if (j==2 || j==5){ cout << "|";}
		}
		if (i==2 || i ==5){
			cout <<endl<< "   -----------------------";
		}
		cout << endl;
	}
	cout << "--------------------------"<< endl;
	cout << "     1 2 3  4 5 6  7 8 9 " << endl;
}

#endif
