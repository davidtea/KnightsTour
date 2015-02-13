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
    XDIM = 8;
    YDIM = 8;
    beenThere = new bool* [XDIM];
    tried = new bool* [XDIM];

    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new bool[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            tried[x][y] = false;
        }
    }
}

Board::Board(int x, int y)
{
    XDIM = x;
    YDIM = y;
    beenThere = new bool* [XDIM];
    tried = new bool* [XDIM];

    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new bool[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            tried[x][y] = false;
        }
    }
}

Board::~Board()
{
    for (int x=0; x<XDIM; ++x)
    {
        delete [] beenThere[x];
        delete [] tried[x];
    }
    delete [] beenThere;
    delete [] tried;
}

vector<coord> Board::checkSpots(const coord& c)
{
    vector<coord> spots;
    if(validSpot(c+UPLEFT)    && !checkBeenThere(c+UPLEFT))
        spots.push_back(c+UPLEFT);
    if(validSpot(c+UPRIGHT)   && !checkBeenThere(c+UPRIGHT))
        spots.push_back(c+UPRIGHT);
    if(validSpot(c+RIGHTUP)   && !checkBeenThere(c+RIGHTUP))
        spots.push_back(c+RIGHTUP);
    if(validSpot(c+RIGHTDOWN) && !checkBeenThere(c+RIGHTDOWN))
        spots.push_back(c+RIGHTDOWN);
    if(validSpot(c+DOWNRIGHT) && !checkBeenThere(c+DOWNRIGHT))
        spots.push_back(c+DOWNRIGHT);
    if(validSpot(c+DOWNLEFT)  && !checkBeenThere(c+DOWNLEFT))
        spots.push_back(c+DOWNLEFT);
    if(validSpot(c+LEFTDOWN)  && !checkBeenThere(c+LEFTDOWN))
        spots.push_back(c+LEFTDOWN);
    if(validSpot(c+LEFTUP)    && !checkBeenThere(c+LEFTUP))
        spots.push_back(c+LEFTUP);
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
    int lowest = 100;
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
    return (c.x >= 0 && c.x < XDIM && c.y >= 0 && c.y < YDIM);
}

bool Board::checkBeenThere(const coord &c)
{
    return beenThere[c.x][c.y];
}

bool Board::checkTried(const coord &c)
{
    return tried[c.x][c.y];
}

void Board::setBeenThere(const coord &c)
{
    beenThere[c.x][c.y] = !beenThere[c.x][c.y];
}

void Board::setTried(const coord &c)
{
    tried[c.x][c.y] = !tried[c.x][c.y];
}

void Board::calculateMoves(const coord &start)
{
    startpos = start;
    moves.push(start);
    setBeenThere(start);
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
//        cin.ignore();
    }
    chessNotation();
    checkClosed() ? cout << "This tour is closed" << endl : cout << "This tour is open" << endl;
}

void Board::doMoves()
{

}

bool Board::checkClosed()
{
    if(startpos+UPLEFT == moves.top())
        return true;
    if(startpos+UPRIGHT == moves.top())
        return true;
    if(startpos+RIGHTUP == moves.top())
        return true;
    if(startpos+RIGHTDOWN == moves.top())
        return true;
    if(startpos+DOWNRIGHT == moves.top())
        return true;
    if(startpos+DOWNLEFT == moves.top())
        return true;
    if(startpos+LEFTDOWN == moves.top())
        return true;
    if(startpos+LEFTUP == moves.top())
        return true;
}

void Board::chessNotation()
{
    //create in order stack of moves
    LinkedStack<coord> copy(moves);
    LinkedStack<coord> reversed(moves.size());
    while(!copy.empty())
        reversed.push(copy.pop());
    //chess notation
    while(!reversed.empty())
    {
        coord temp = reversed.pop();
        char x = 'a' + temp.x;
        char y = '1' + temp.y;
        cout << x << y << " ";
    }
    // do each starting position and find all closed tours
}

void Board::print()
{
    cout << "Dimension: " << XDIM << "x" << YDIM << endl;
    for (int y=YDIM-1; y>=0; --y)
    {
        for (int x=0; x<XDIM; ++x)
        {
            if(coord(x,y) == startpos)
                cout << "1 ";
            else if(coord(x,y) == moves.top())
                cout << "0 ";
            else if(beenThere[x][y])
                cout << "X ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}
