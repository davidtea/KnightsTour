#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "LinkedStack.h"
#include "coord.h"

using namespace std;

class Board
{
public:
    Board();
    ~Board();

    //LinkedStack of coord
    vector<coord> checkSpots(const coord &c);
    vector<int> checkPossibleSpots(const vector<coord> &checkThese);
    int findLeastMoves(const vector<int> &fromThese);

    bool validSpot(const coord &c);
    bool checkBeenThere(const coord &c);
    bool checkTried(const coord &c);
    void setBeenThere(const coord &c);
    void setTried(const coord &c);
    void calculateMoves(const coord &start);
    void doMoves();

    void print();

private:
    bool beenThere [8][8];
    bool tried [8][8];
    LinkedStack<coord> moves;
};


#endif // BOARD_H
