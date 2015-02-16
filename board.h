#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cstdio>
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
    vector<coord> checkSpots(const coord &c, const coord &ignoreThis = coord(-1,-1));
    vector<int> checkPossibleSpots(const vector<coord> &checkThese);
    int findLeastMoves(const vector<int> &fromThese);

    bool validSpot(const coord &c);
    bool checkBeenThere(const coord &c);
    int checkTried(const coord &c);
    void setBeenThere(const coord &c);
    void setTried(const coord &c);
    void setHistory(const coord &c);
    void resetTried();
    void calculateMoves(const coord &start);
    void doMoves();
    bool checkClosed();
    coord backtrack();

    void chessNotation();
    void print();

private:
    int XDIM;
    int YDIM;
    coord startpos;
    bool **beenThere;
    int  **history;
    int  **tried;
    LinkedStack<coord> moves;
};


#endif // BOARD_H
