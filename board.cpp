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
    tried = new int* [XDIM];
    history = new int* [XDIM];

    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new int[YDIM];
        history[x] = new int[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            tried[x][y] = 0;
            history[x][y] = 0;
        }
    }
}

Board::Board(int x, int y)
{
    XDIM = x;
    YDIM = y;
    beenThere = new bool* [XDIM];
    tried = new int* [XDIM];
    history = new int* [XDIM];

    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new int[YDIM];
        history[x] = new int[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            tried[x][y] = 0;
            history[x][y] = 0;
        }
    }
}

Board::~Board()
{
    for (int x=0; x<XDIM; ++x)
    {
        delete [] beenThere[x];
        delete [] tried[x];
        delete [] history[x];
    }
    delete [] beenThere;
    delete [] tried;
    delete [] history;
}

vector<coord> Board::checkSpots(const coord& c, const coord& ignoreThis)
{
    vector<coord> spots;
    coord array[8] = {c+UPLEFT, c+UPRIGHT, c+RIGHTUP, c+RIGHTDOWN, c+DOWNRIGHT, c+DOWNLEFT, c+LEFTDOWN, c+LEFTUP};
    for(int i=0; i<8; ++i)
    {
        if(validSpot(array[i]) && !checkBeenThere(array[i]) && array[i] != ignoreThis && moves.size() != checkTried(array[i]))
        {
            if(array[i] == endpos && moves.size() < XDIM*YDIM - 1);
            else
                spots.push_back(array[i]);
        }


    }
//    cout<<spots.size()<<endl;
//    for(int i=0; i<spots.size(); ++i)
//        cout << spots[i] << endl;
    return spots;
}

vector<int> Board::checkPossibleSpots(const vector<coord> &checkThese)
{
    vector<coord> temp;
    vector<int> numberOfMoves;
    for(unsigned int i=0; i<checkThese.size(); ++i)
    {
        temp = checkSpots(checkThese[i]);
        numberOfMoves.push_back(temp.size());
    }
    return numberOfMoves;
}

int Board::findLeastMoves(const vector<int> &fromThese)
{
    srand (time(NULL));
    int lowest = 8;
    vector<int> lows;
    int place = 0;
    for (unsigned int i=0; i<fromThese.size(); ++i)
    {
        if(fromThese[i] < lowest)
        {
            lowest = fromThese[i];
            place = i;
        }
    }
    for (unsigned int i=0; i<fromThese.size(); ++i)
    {
        if(fromThese[i] == lowest)
            lows.push_back(i);
    }
    int i = lows.size();
    i > 1 && (place = rand() % i);
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

int Board::checkTried(const coord &c)
{
    return tried[c.x][c.y];
}

void Board::setBeenThere(const coord &c)
{
    beenThere[c.x][c.y] = !beenThere[c.x][c.y];
}

void Board::setTried(const coord &c)
{
    tried[c.x][c.y] = moves.size();
}

void Board::resetTried()
{
    for(int x=0; x<XDIM; ++x)
        for(int y=0; y<YDIM; ++y)
            tried[x][y] = 0;
}

void Board::setHistory(const coord &c)
{
    //use () ? :
    if(history[c.x][c.y] == 0)
        history[c.x][c.y] = moves.size();
    else
        history[c.x][c.y] = 0;
}

void Board::calculateMoves(const coord &start, const coord &end)
{
    startpos = start;
    endpos = end;
    moves.push(start);
    setBeenThere(start);
    setHistory(start);
    print();
//    cin.ignore();
    while(!moves.full())
    {
        coord temp;
        vector<coord> check = checkSpots(moves.top());
        while(check.size() == 0)
        {
            temp = backtrack();
            check = checkSpots(moves.top(), temp);
//            cout << "Backtrack" << endl;
            print();
//            cin.ignore();
        }
        vector<int> possible = checkPossibleSpots(check);
        int place = findLeastMoves(possible);
        temp = check[place];
        moves.push(temp);
        setBeenThere(temp);
        setHistory(temp);
        print();
//        cin.ignore();
    }

}

coord Board::backtrack()
{
    //reset then backtrack?
    coord nogood = moves.pop();
    if(moves.size() == 1)
        resetTried();
    setBeenThere(nogood);
    setHistory(nogood);
    setTried(nogood);
    return nogood;
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
    return false;
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
        cout << 'N' << x << y << " ";
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
            if(history[x][y] != 0)
                printf("%-3d", history[x][y]);
            else
                cout << "-  ";
        }
//        this is used to check for tried

        cout << "   ";
        for (int x=0; x<XDIM; ++x)
        {
            if(tried[x][y] != 0)
                printf("%-3d", tried[x][y]);
            else
                cout << "-  ";
        }
        cout << endl;
    }
}
