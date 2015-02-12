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
    moves.resize(65);
    for (int x=0; x<8; ++x)
    {
        for (int y=0; y<8; ++y)
        {
            beenThere[x][y] = false;
            tried[x][y] = false;
        }
    }
}

Board::~Board()
{

}

vector<coord> Board::checkSpots(const coord& c)
{
    vector<coord> spots;
    if(validSpot(c+UPLEFT)    && checkBeenThere(c+UPLEFT))
    {
        spots.push_back(c+UPLEFT);
    }
    if(validSpot(c+UPRIGHT)   && checkBeenThere(c+UPRIGHT))
    {
        spots.push_back(c+UPRIGHT);
    }
    if(validSpot(c+RIGHTUP)   && checkBeenThere(c+RIGHTUP))
    {
        spots.push_back(c+RIGHTUP);
    }
    if(validSpot(c+RIGHTDOWN) && checkBeenThere(c+RIGHTDOWN))
    {
        spots.push_back(c+RIGHTDOWN);
    }
    if(validSpot(c+DOWNRIGHT) && checkBeenThere(c+DOWNRIGHT))
    {
        spots.push_back(c+DOWNRIGHT);
    }
    if(validSpot(c+DOWNLEFT)  && checkBeenThere(c+DOWNLEFT))
    {
        spots.push_back(c+DOWNLEFT);
    }
    if(validSpot(c+LEFTDOWN)  && checkBeenThere(c+LEFTDOWN))
    {
        spots.push_back(c+LEFTDOWN);
    }
    if(validSpot(c+LEFTUP)    && checkBeenThere(c+LEFTUP))
    {
        spots.push_back(c+LEFTUP);
    }
    cout <<"size:" << spots.size() << endl;
    for(int i=0; i<spots.size(); ++i)
    {
        cout << spots[i] << "  ";
    }
    cout << endl;
    return spots;
}

vector<int> Board::checkPossibleSpots(const vector<coord> &checkThese)
{
    vector<coord> temp;
    vector<int> numberOfMoves;
    for(int i=0; i<checkThese.size(); ++i)
    {
        cout << "For: " << i << ": " << checkThese[i] << endl;
        temp = checkSpots(checkThese[i]);
        numberOfMoves.push_back(temp.size());
    }
    return numberOfMoves;
}

int Board::findLeastMoves(const vector<int> &fromThese)
{
    int lowest = 10;
    int place;
    for (int i=0; i<fromThese.size(); ++i)
    {
        if(fromThese[i] < lowest)
        {
            lowest = fromThese[i];
            place = i;
        }
    }
    return place;
}


bool Board::validSpot(const coord &c)
{
    return (c.x >= 0 && c.x < 8 && c.y >= 0 && c.y < 8);
}

bool Board::checkBeenThere(const coord &c)
{
    return !beenThere[c.x][c.y];
}

bool Board::checkTried(const coord &c)
{
    return tried[c.x][c.y];
}

void Board::setBeenThere(const coord &c)
{
    beenThere[c.x][c.y] = true;
}

void Board::setTried(const coord &c)
{
    tried[c.x][c.y] = true;
}

void Board::calculateMoves(const coord &start)
{
    moves.push(start);
    while(!moves.full())
    {
        vector<coord> check = checkSpots(moves.top());
        vector<int> possible = checkPossibleSpots(check);
        int place = findLeastMoves(possible);
        coord temp = check[place];
        moves.push(temp);
        setBeenThere(temp);
        cout << "Moves size: " << moves.size() <<endl;
        print();
    }
}

void Board::doMoves()
{

}

void Board::print()
{
    cout << endl;
    for (int x=0; x<8; ++x)
    {
        for (int y=0; y<8; ++y)
        {
            if(beenThere[x][y])
                cout << "X";
            else
                cout << "_";
        }
        cout << endl;
    }
}
