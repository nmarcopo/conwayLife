# Fundamentals of Computing Project: Conway's Game of Life
Originally submitted on November 7, 2017 to professor [Ramzi Bualuan](https://engineering.nd.edu/profiles/rbualuan)

# Addendum:
## TL;DR: Compile the program with `make`, run with `./playlife scene[12345].txt`
This course was the first computer science course I took at Notre Dame. I learned the basics of C++ and developed a strong foundation for CS as a whole. The class was structured so that we had a project every week, with each week getting more and more complex. The "Conway's Game of Life" project was the beginning of the more complex projects, where we needed to use a `Makefile`, header files, etc.  
I knew about Conway's Game of Life before this project, from carykh's [YouTube channel](https://www.youtube.com/user/carykh). Check his channel out - he's a talented guy who's really good at explaining tough CS concepts.  
Below is the original readme file I submitted to Ramzi; I've made a few spelling changes to it. It details the functionality of the program, as well as gives the instructions for running the program in "Interactive" and "Batch" mode. Sources for my the life forms from my scene files are at the end.

# Original Readme:
Nicholas Marcopoli  
Fundamentals of Computing Lab - Section 01  
11-7-2017  

From the user's perspective, the program starts its functionality at the command line. If the user simply types "playlife" at the terminal, the program will enter interactive mode, which will be detailed below. If the user types "playlife" and then enters the name of a data file, the program will enter batch mode, which will also be detailed below. If the user enters too many commands on the command line, the program will return an error message.  
Interactive mode allows the user to create and kill cells on a 40x40 Conway's Game of Life board. If the user types 'a' and enters the coordinates of a cell, a live cell will be created in this spot. If the user types 'r' and enters the coordinates of a cell, any live cell in this spot will be killed. If the user types 'n', the board will advance one stage in the Game of Life, applying the rules of life as defined in the Lab 8 instructions. If the user types 'p', the board will animate the Game of Life until the user types Ctrl-C.  
Batch mode allows the user to input a data file with the information of an initial setup for Life. For example, if a file containing the life form "glider" is input into the program, the glider will be created as if the user had input its living coordinates in Interactive mode, and it will be animated as if the user had input 'p' in interactive mode. This way, scenes that may take a long time to input can be easily be displayed.  

From a programming perspective, the program uses argc and argv[] to detect and use command line arguments. If argc is 1, then the main driver executes the interactive() function. If argc is 2, the program passes the command line argument to the batch() function.  
The most important functionality of the program lies in the lifeboard.cpp file, in the printBoard() internal method. This method displays the entire 40x40 board on screen with each cell indicating life or death. If a cell is marked with an X, it is alive, and if it is blank, it is dead. To achieve this, the command system("clear") is executed to clear the whole terminal window. The top border of the board is printed using a for loop, with spaces in between to compensate for the fact that each cell's height is twice its width. The elements of lifeArr are then printed using nested for loops and the printStatus() member function, which will print X if the cell is alive and a space if it is dead. The outer borders are created by inserting '=' before and after each row is printed. A space is printed between each cell, similar to the top border. The bottom border is then added in the same way as the top border.  

In the interactive() function, the object 'board' is created from the Life class, defined in the files lifeboard.h and lifeboard.cpp. Objects of this class contain two entire 40x40 Life boards as bool arrays, one for the current board, and one to evaluate the next turn.  
The program receives input from the user to decide which command will be run. If the user types a and two coordinates, the .addLife() method is executed, which adds a living cell to the board at that user specified spot by simply calling the setStatus() member function, which sets the respective element of the bool array lifeArr to true.  
If the user types r and two coordinates, the .killLife() method is executed, which kills a living cell to the board at that user specified spot by simply calling the setStatus() member function, which sets the respective element of the bool array lifeArr to false.  
If the user types n, the .iterateLife() method is executed, which applies the rules of Conway's Game of Life to advance the game one turn. First, the lifeArr is copied into the second array contained in the Life class, previousLife. This allows the program to make comparisons in lifeArr, but make changes in previousLife, so not as to affect future changes and mess up the rules of Life. The program then uses the checkNeighbors() member function to see how many adjacent live cells surround each cell. If any cell has exactly 3 adjacent cells, it will become alive. If a cell is alive and has two adjacent cells, it will stay alive. For any other case, the cell will become dead. Additionally, the checkNeighbor() function allows the board to wrap around itself, and thus for cells along the edges of the board it will check the opposite edge as well. It does this using the formula (x + BOARDSIZE) % BOARDSIZE. You can find the link to this formula within lifeboard.cpp. The screen will then print the results of the iteration.  
If the user types p, the .continuousLife() method is called, which calls the iterateLife() menu function and the usleep() function within an infinite while loop so as to animate the Game of Life until the user presses ctrl-c.  

In the batch function, a data file is loaded in using an ifstream in conjunction with a vector of strings. The ifs is loaded in using getline(), each line of the file is stored in a string, and the string is pushed back into the vector until there is nothing left in the file. Next, the commands contained in the file are executed. A for loop is used with iterators to iterate through the vector of commands. A stringstream is used to search through each line of the vector for commands. The program evaluates the first letter of the string and decides what method to execute, similar to the way the interactive() function works. If the 'a' or 'r' commands are executed, the program uses the getline() function with the stringstream to sift through the string for the coordinates of a cell to bring to life or kill. If the 'n' or 'p' commands are executed, the program functions the same way that the interactive() function does.  

I verified the output of my program by looking at Conway's Game of Life simulations online, and found that my program gave the same output that a typical Game of Life would give. The program's wrapping around of the board functioned correctly as well, which was extensively tested through the scenes I created, particularly scene 3. This project was a lot of fun, definitely my favorite so far!  

I've listed the sources for each of my scenes below:  

Sources for each of my scenes:  
scene1.txt:  
eater 1, from http://www.conwaylife.com/wiki/Eater_1  
boat-ship-tie, from http://www.conwaylife.com/wiki/Boat-ship-tie  
Big S, from http://www.conwaylife.com/wiki/Big_S  
hat, from http://www.conwaylife.com/wiki/Hat  

scene2.txt:  
blinker, from http://www.conwaylife.com/wiki/Blinker  
clock, from http://www.conwaylife.com/wiki/Clock  
figure 8, from http://www.conwaylife.com/wiki/Figure_eight  
toad, from http://www.conwaylife.com/wiki/Toad  

scene3.txt:  
// initially move in different directions, but then they hit each other and go wacky  
Lightweight spaceship, from http://www.conwaylife.com/wiki/Lightweight_spaceship  
Loafer, from http://www.conwaylife.com/wiki/Loafer  
glider, from given file  
middleweight spaceship, from http://www.conwaylife.com/wiki/Middleweight_spaceship  

scene4.txt:  
Lightweight spaceship, from http://www.conwaylife.com/wiki/Lightweight_spaceship  
Loafer, from http://www.conwaylife.com/wiki/Loafer  

scene5.txt:  
Lightweight spaceship, from http://www.conwaylife.com/wiki/Lightweight_spaceship  
Loafer, from http://www.conwaylife.com/wiki/Loafer  
