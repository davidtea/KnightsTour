#ifndef BOARD_H
#define BOARD_H

#include "Stack.h"
#include "coord.h"

using namespace std;

class Board
{
public:
    Board();
    ~Board();

    //Stack of coord
    Stack<coord>& checkSpots(const coord &c);
    Stack<int> &checkPossibleSpots(const coord &c, const Stack<coord> &checkThese);
    bool validSpot(const coord &c);
    bool checkBeenThere(const coord &c);
    bool checkTried(const coord &c);
    void calculateMoves(const coord &start);
    void doMoves();

private:
    bool beenThere [8][8];
    bool tried [8][8];
    Stack<coord> moves;
};


#endif // BOARD_H
