#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdio>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "LinkedStack.h"
#include "coord.h"

using namespace std;

class Board
{
public:
    Board();
    Board(int x, int y);
    ~Board();

    //LinkedStack of coord
    vector<coord> checkSpots(const coord &c, const coord &ignoreThis = coord(-1,-1)); //checks all spots the knight can make from that square
    vector<int> checkPossibleSpots(const vector<coord> &checkThese); //from one of the initial squares, finds the next one with the least moves
    void sortPossibles(vector<coord> &spots, vector<int> &possible); //sorts the order of moves from least to greatest number of moves

    void resetAll();
    void addTry(const coord &c); //adds to vector of last the next move
    void clearTry(const coord &c); //clears the last vector of moves when backtracking
    bool validSpot(const coord &c); //if it exists on the board and haven't been there or tried yet and not the end pos unless it's the end
    bool checkBeenThere(const coord &c); //check if knight has been to that sqaure yet
    bool checkTried(const coord &c); //check if knight has tried that square when backtracking
    void setBeenThere(const coord &c); //changes that square's state of beenThere
    void setHistory(const coord &c); //records the knights sequence of moves around the board
    bool findEnd(); //used when user wants an ending point as well, otherwise just finds any solution with given start
    bool calculateMoves(const coord &start, const coord &end); //calculates the tour
    coord backtrack(); //goes back one move if it reaches a dead end, sets tried
    bool checkClosed(); //checks if tour is closed of not

    void setStart(const coord &c);
    void setEnd(const coord &c);

    void generateClosedTours(ofstream &out); //used for finding closed tours, cannot find all of them though
    bool closedTour(); //same as setEnd except for outputting to file, and stops a search after 5 secs.

    void chessNotation(); //shows the knight's tour in chess notation
    void print(); //prints the board

    friend
    ostream& operator<<(ostream &out, const Board &b); //chess notation

private:
    int XDIM; //x dimension of board
    int YDIM; //y dimension of board
    coord startpos; //starting point
    coord endpos; //ending point
    bool **beenThere; //2D array of bools to represent where knight has gone
    int  **history; //2D of ints to represent the knights sequence of moves
    vector<coord>  **tried; //2D array of vectors for each square to record which ones have been  tried, for backtracking
    LinkedStack<coord> moves; //stack of moves knight has made
};


#endif // BOARD_H
