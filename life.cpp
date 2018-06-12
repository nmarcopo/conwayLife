// Nicholas Marcopoli
// Fundamentals of Computing Lab - Section 01
// 11-5-2017
// Main Driver for Conway's Game of Life

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "lifeboard.h"
using namespace std;

#define BOARDSIZE 40

// Function prototypes
// Modes
int interactive();
int batch(char*);

int main(int argc, char *argv[]){
	
	// Chooses which mode to run
	// Returns an error if there are more than 2 args
	if(argc == 1) return interactive();
	else if(argc == 2) return batch(argv[1]);
	else{
		cout << "Error, please do not enter more than 2 command line arguments." << endl;
		return 1;
	}
	
}

// Excecute interactive Life
int interactive(){
	Life board;
	board.printBoard("init"); // Create a blank board
	
	bool exit = false;
	while(!exit){
		// Initialize variables outside of switch
		char choice;
		int xPos, yPos;
		
		// Set up board and accept command
		board.printBoard();
		cout << "INTERACTIVE: Enter a command. Origin is in the top left corner." << endl;
		cin >> choice;
		
		switch(choice){
			case 'a':
				cout << "Enter coordinate where live cell should be added: ";
				cin >> xPos >> yPos;
				board.addLife(xPos, yPos);
				break;
			case 'r':
				cout << "Enter coordinate where cell should be killed: ";
				cin >> xPos >> yPos;
				board.killLife(xPos, yPos);
				break;
			case 'n':
				board.iterateLife();
				break;
			case 'p':
				board.continuousLife();
				break;
			case 'q':
				cout << "Exiting Life..." << endl;
				exit = true;
				break;
			default:
				cout << "choose again" << endl;
				break;
		}
	}
	
	return 0;
}

// Excecute Life using data file
int batch(char *s){
	
	Life board;
	
	// Load data file into vector
	ifstream ifs;
	
	ifs.open(s);
	if(!ifs){
		cout << "ERROR OPENING FILE, EXITING..." << endl;
		return 1;
	}
	
	board.printBoard("init");

    vector<string> commandVect;
    string command;
    while(ifs.peek() != EOF){
        getline(ifs, command);
        commandVect.push_back(command);
    }
    
    for(auto it = commandVect.begin(); it != commandVect.end(); it++){
        command = *it;
        stringstream ss(command);
        string skip, x, y;
        
        // checks commands sent by the data file
        if(command[0] == 'a'){
			getline(ss, skip, ' '); // skip over first command
			getline(ss, x, ' '); // input first number
			getline(ss, y, '\n'); // input second number
            board.addLife(stoi(x), stoi(y)); // add life at specified point
        }
        if(command[0] == 'r'){
			getline(ss, skip, ' '); // skip over first command
			getline(ss, x, ' '); // input first number
			getline(ss, y, '\n'); // input second number
            board.killLife(stoi(x), stoi(y)); // kill life at specified point
		}
		if(command[0] == 'n'){
			board.iterateLife();
		}
        if(command[0] == 'p'){
			board.continuousLife();
		}
        
    }
    
    board.printBoard();
    
	return 0;
}
