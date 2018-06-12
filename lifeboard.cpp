// Nicholas Marcopoli
// Fundamentals of Computing Lab - Section 01
// 11-5-2017
// Implementation for Life Class

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>

#include "lifeboard.h"
using namespace std;

Life::Life(){ }

Life::~Life(){ }

// Access Methods
bool Life::getStatus(int x, int y){
	return lifeArr[x][y]; // true when alive, false when dead
}

void Life::setStatus(bool b, int x, int y){
	lifeArr[x][y] = b;
}

// Internal Methods
int Life::checkNeighbors(int x, int y){
	int liveNeighbors = 0;
	
	// Wraps around screen, idea from:
	// https://stackoverflow.com/questions/32654256/wrapping-conways-game-of-life-c
	// Check top left
	if(getStatus(((x-1) + BOARDSIZE) % BOARDSIZE, ((y-1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check top middle
	if(getStatus(((x) + BOARDSIZE) % BOARDSIZE, ((y-1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check top right
	if(getStatus(((x+1) + BOARDSIZE) % BOARDSIZE, ((y-1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check left
	if(getStatus(((x-1) + BOARDSIZE) % BOARDSIZE, ((y) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check right
	if(getStatus(((x+1) + BOARDSIZE) % BOARDSIZE, ((y) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check bottom left
	if(getStatus(((x-1) + BOARDSIZE) % BOARDSIZE, ((y+1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check bottom middle
	if(getStatus(((x) + BOARDSIZE) % BOARDSIZE, ((y+1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;
	// Check bottom right
	if(getStatus(((x+1) + BOARDSIZE) % BOARDSIZE, ((y+1) + BOARDSIZE) % BOARDSIZE) == true) liveNeighbors++;

	return liveNeighbors;
}

void Life::iterateLife(){
	
	// Copy lifeArr into previousLife
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			previousLife[i][j] = lifeArr[i][j];
		}
	}
	
	// Apply rules of life to previousLife
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			if(checkNeighbors(i, j) == 3) previousLife[i][j] = true;
			else if(checkNeighbors(i, j) == 2 && lifeArr[i][j] == true); // do nothing since it's already alive
			else previousLife[i][j] = false;
		}
	}
	
	// Copy previousLife into lifeArr
	for(int i = 0; i < BOARDSIZE; i++){
		for(int j = 0; j < BOARDSIZE; j++){
			lifeArr[i][j] = previousLife[i][j];
		}
	}
	printBoard();
}

// Utility Methods

char Life::printStatus(int x, int y){
	if(lifeArr[x][y] == true) cout << "X";
	else cout << " ";
}

void Life::printBoard(string s){
	// Clear terminal
	system("clear");
	
	// Setup border around top of board
	for(int i = 0; i <= BOARDSIZE+1; i++) cout << "= "; // +1 for formatting
	cout << endl;
	
	// Setup Life objects on board
	for(int i = 0; i < BOARDSIZE; i++){
		cout << "= ";
		for(int j = 0; j < BOARDSIZE; j++){
			if(s == "init") lifeArr[i][j] = false;
			printStatus(j, i);
			cout << " ";
		}
		cout << "=" << endl;
	}
	for(int i = 0; i <= BOARDSIZE+1; i++) cout << "= "; // +1 for formatting
	cout << endl;
}

// If a user does not want to initialize board, don't pass any string
// then this function will pass a placeholder string so that board is not
// initialized.
void Life::printBoard(){
	printBoard("notinit");
}


// Adds a live cell to a specified position
void Life::addLife(int x, int y){
	setStatus(true, x, y);
}

// Kills a cell on a specified position
void Life::killLife(int x, int y){
	setStatus(false, x, y);
}

void Life::continuousLife(){
	while(true){
		iterateLife();
		usleep(80000);
	}
}
