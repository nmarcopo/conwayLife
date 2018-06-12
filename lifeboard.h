// Nicholas Marcopoli
// Fundamentals of Computing Lab - Section 01
// 11-5-2017
// Interface for Life class
using namespace std;
#define BOARDSIZE 40

class Life {
public:
	Life();
	~Life();
	
	// Access Methods
	bool getStatus(int, int);
	void setStatus(bool, int, int);
	
	// Internal Methods
	int checkNeighbors(int, int);
	void iterateLife();
	
	// Utility Methods
	char printStatus(int, int);
	void printBoard();
	void printBoard(string);
	void addLife(int, int);
	void killLife(int, int);
	void continuousLife();
	
private:
	bool lifeArr[BOARDSIZE][BOARDSIZE];
	bool previousLife[BOARDSIZE][BOARDSIZE];
};
