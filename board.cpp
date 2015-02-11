#include "board.h"

const coord UPLEFT(-1,2);
const coord UPRIGHT(1,2);
const coord RIGHTUP(2,1);
const coord RIGHTDOWN(2,-1);
const coord DOWNRIGHT(1,-2);
const coord DOWNLEFT(-1,-2);
const coord LEFTDOWN(-2,-1);
const coord LEFTUP(-2,1);

Board::Board()
{

}

Board::~Board()
{

}

Stack<coord>& Board::checkSpots(const coord& c)
{
    Stack<coord> spots(8);
    if(checkBeenThere(c+UPLEFT) && validSpot(c+UPLEFT) )
        spots.push(c+UPLEFT);
    if(checkBeenThere(c+UPRIGHT) && validSpot(c+UPRIGHT) )
        spots.push(c+UPRIGHT);
    if(checkBeenThere(c+RIGHTUP) && validSpot(c+RIGHTUP) )
        spots.push(c+RIGHTUP);
    if(checkBeenThere(c+RIGHTDOWN) && validSpot(c+RIGHTDOWN) )
        spots.push(c+RIGHTDOWN);
    if(checkBeenThere(c+DOWNRIGHT) && validSpot(c+DOWNRIGHT) )
        spots.push(c+DOWNRIGHT);
    if(checkBeenThere(c+DOWNLEFT) && validSpot(c+DOWNLEFT) )
        spots.push(c+DOWNLEFT);
    if(checkBeenThere(c+LEFTDOWN) && validSpot(c+LEFTDOWN) )
        spots.push(c+LEFTDOWN);
    if(checkBeenThere(c+LEFTUP) && validSpot(c+LEFTUP) )
        spots.push(c+LEFTUP);
//    cout << spots;
    return spots;
}

Stack<int>& Board::checkPossibleSpots(const coord& c, const Stack<coord> &checkThese)
{
    Stack<coord> spots(checkThese);
    Stack<int> numberOfMoves(8);
    while(!spots.empty())
    {
        int i = checkSpots(spots.pop()).size();
        numberOfMoves.push(i);
    }
    return numberOfMoves;
}

bool Board::validSpot(const coord &c)
{
    return (c.x >= 0 && c.x <= 8 && c.y >= 0 && c.y <= 8);
}

bool Board::checkBeenThere(const coord &c)
{
    return beenThere[c.x][c.y];
}

bool Board::checkTried(const coord &c)
{
    return tried[c.x][c.y];
}

void Board::calculateMoves(const coord &start)
{
    while(!moves.full())
    {
        Stack<coord> temp = checkSpots(start);
    }
}

void Board::doMoves()
{

}
