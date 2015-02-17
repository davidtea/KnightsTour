#include "qBoard.h"

const coord UPLEFT(-1,2);
const coord UPRIGHT(1,2);
const coord RIGHTUP(2,1);
const coord RIGHTDOWN(2,-1);
const coord DOWNRIGHT(1,-2);
const coord DOWNLEFT(-1,-2);
const coord LEFTDOWN(-2,-1);
const coord LEFTUP(-2,1);

qBoard::qBoard()
{
    XDIM = 8;
    YDIM = 8;
    beenThere = new bool* [XDIM];
    tried = new vector<coord>* [XDIM];
    history = new int* [XDIM];
    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new vector<coord>[YDIM];
        history[x] = new int[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            history[x][y] = 0;
        }
    }
}

qBoard::qBoard(int x, int y)
{
    XDIM = x;
    YDIM = y;
    beenThere = new bool* [XDIM];
    tried = new vector<coord>* [XDIM];
    history = new int* [XDIM];
    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new vector<coord>[YDIM];
        history[x] = new int[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            history[x][y] = 0;
        }
    }
}

qBoard::~qBoard()
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
    moves.clear();
}

void qBoard::resetAll()
{
    beenThere = new bool* [XDIM];
    tried = new vector<coord>* [XDIM];
    history = new int* [XDIM];
    moves.resize(XDIM * YDIM);
    for (int x=0; x<XDIM; ++x)
    {
        beenThere[x] = new bool[YDIM];
        tried[x] = new vector<coord>[YDIM];
        history[x] = new int[YDIM];
        for (int y=0; y<YDIM; ++y)
        {
            beenThere[x][y] = false;
            history[x][y] = 0;
        }
    }
    moves.clear();
}

vector<coord> qBoard::checkSpots(const coord& c, const coord& ignoreThis)
{
    vector<coord> spots; //all moves a knight can make
    coord array[8] = {c+UPLEFT, c+UPRIGHT, c+RIGHTUP, c+RIGHTDOWN, c+DOWNRIGHT, c+DOWNLEFT, c+LEFTDOWN, c+LEFTUP};
    for(int i=0; i<8; ++i)
    {
        if(validSpot(array[i]) && !checkBeenThere(array[i]) && array[i] != ignoreThis && !checkTried(array[i]))
        {
            if(array[i] == endpos && moves.size() < XDIM*YDIM - 1);
                // not time to go there yet
            else
                spots.push_back(array[i]); //add move to vector to be returned
        }
    }
    return spots;
}

vector<coord> qBoard::checkValidSpots(const coord &c)
{
    vector<coord> spots; //all moves a knight can make
    coord array[8] = {c+UPLEFT, c+UPRIGHT, c+RIGHTUP, c+RIGHTDOWN, c+DOWNRIGHT, c+DOWNLEFT, c+LEFTDOWN, c+LEFTUP};
    for(int i=0; i<8; ++i)
    {
        if(validSpot(array[i]))
        {
            spots.push_back(array[i]); //add move to vector to be returned
        }
    }
    return spots;
}

vector<int> qBoard::checkPossibleSpots(const vector<coord> &checkThese)
{
    vector<coord> temp;
    vector<int> numberOfMoves; //numbers will correspond to squares taken from checkspots
    for(unsigned int i=0; i<checkThese.size(); ++i)
    {
        temp = checkSpots(checkThese[i]); //checks number of spots for each potential move
        numberOfMoves.push_back(temp.size()); //adds the number of moves to int vector
    }
    return numberOfMoves;
}

void qBoard::sortPossibles(vector<coord> &spots, vector<int> &possible)
{
    // sort moves by least possible to greatest by swapping
    for(unsigned int i=0; i<possible.size(); ++i)
    {
        for(unsigned int j=i; j<possible.size(); ++j)
        {
            if(possible[j] < possible[i])
            {
                int itemp;
                itemp = possible[i];
                possible[i] = possible[j];
                possible[j] = itemp;
                coord ctemp;
                ctemp = spots[i];
                spots[i] = spots[j];
                spots[j] = ctemp;
            }
        }
    }
}

void qBoard::addTry(const coord &c) //from whatever was backtracked to, record what was tried so it wont repeat
{
    tried[moves.front().getX()][moves.front().getY()].push_back(c);
}

void qBoard::clearTry(const coord &c) //clears the tries so that when it backtracks and gets back to it, it can try all possibilities
{
    tried[c.getX()][c.getY()].clear();
}

bool qBoard::validSpot(const coord &c)
{
    return (c.getX() >= 0 && c.getX() < XDIM && c.getY() >= 0 && c.getY() < YDIM);
}

bool qBoard::checkBeenThere(const coord &c)
{
    return beenThere[c.getX()][c.getY()];
}

bool qBoard::checkTried(const coord &c)
{
    for(unsigned int i=0; i<tried[moves.front().getX()][moves.front().getY()].size(); ++i)
        if(tried[moves.front().getX()][moves.front().getY()].at(i) == c)
            return true;
    return false;
}

void qBoard::setBeenThere(const coord &c)
{
    beenThere[c.getX()][c.getY()] = !beenThere[c.getX()][c.getY()];
}

void qBoard::setHistory(const coord &c)
{
    (history[c.getX()][c.getY()] == 0) ? history[c.getX()][c.getY()] = moves.size(): history[c.getX()][c.getY()] = 0;
}

bool qBoard::findEnd()
{
    coord pos = startpos;
    coord next;
    moves.enqueue(pos, moves.size()); //enqueue starting pos to stack
    setBeenThere(pos); //sets satarting pos as beenThere
    setHistory(pos); //sets starting pos as move 1
    cout << "Finding a solution. Please wait. It will be a while..." << endl;
    while(!moves.empty()) //if empty, that means backtracked all the way back and no solution
    {
        pos = moves.front(); //each loop, set pos to last move
        vector<coord> check = checkSpots(pos); //next moves knight can make
        while(check.size() == 0) //reaches a dead end
        {
            next = backtrack(); //backtracks, dequeues and unsets beenthere, history
            if(moves.size() == 0) //tried every combination of moves but no solution, it dequeueped everything off stack
                return false;
            check = checkSpots(moves.front(), next); //checkspots ignores the 'next', the deadend move and any other tried moves

        }
        vector<int> possible = checkPossibleSpots(check); //gets number of possible moves each square from checkspots has
        sortPossibles(check, possible); //sorts from least to greatest, try least amount first
        pos = check[0]; // least amount of possible moves will be first in array
        addTry(pos); // sets the next move as a tried move so it will not try again when backtracked here
        moves.enqueue(pos, moves.size()); //adds the new move to the stack
        setBeenThere(pos); //set that knight has been there
        setHistory(pos); //set move number of new move

        if (moves.full()) //when solution is found, stack will be full
            return true;
    }
    return false; //default case, no solution
}

bool qBoard::calculateMoves(const coord &start, const coord &end)
{
    startpos = start; //set starting pos
    endpos = end; //set ending pos
    return findEnd();
}

void qBoard::generateClosedTours(ofstream &out)
{
    out << "Closed Tours of qBoard with Dimension: " << XDIM << "x" << YDIM << endl;
    for(int x=0; x<XDIM; ++x)
    {
        for(int y=0; y<YDIM; ++y)
        {
            startpos = coord(x,y);
            vector<coord> check = checkValidSpots(startpos); //find possible moves from start
            for(unsigned int i=0; i<check.size(); ++i)
            {
                endpos = check[i]; //makes sure endpos is last move
                cout << startpos << "->" << endpos;
                if(closedTour())
                {
                    cout << "SUCCESS" << endl;
                    out << *this << endl;
                }
                else
                    cout << "FAIL" << endl;
                resetAll();
            }
        }
    }
}

bool qBoard::closedTour()
{
    clock_t tstart = clock();
    coord pos = startpos;
    coord next;
    moves.enqueue(startpos, moves.size()); //enqueue starting pos to stack
    setBeenThere(startpos); //sets starting pos as beenThere
    setHistory(startpos); //sets starting pos as move 1
    while(!moves.empty()) //if empty, that means backtracked all the way back and no solution
    {
        if((double)(clock() - tstart)/CLOCKS_PER_SEC >= 1.5) //if it takes more than 5secs to find, just skip it
            return false;
        pos = moves.front(); //each loop, set pos to last move
        vector<coord> check = checkSpots(pos); //next moves knight can make
        while(check.size() == 0) //reaches a dead end
        {
            next = backtrack(); //backtracks, dequeues and unsets beenthere, history
            if(moves.size() == 0) //tried every combination of moves but no solution, it dequeueped everything off stack
                return false;
            check = checkSpots(moves.front(), next); //checkspots ignores the 'next', the deadend move and any other tried moves

        }
        vector<int> possible = checkPossibleSpots(check); //gets number of possible moves each square from checkspots has
        sortPossibles(check, possible); //sorts from least to greatest, try least amount first
        pos = check[0]; // least amount of possible moves will be first in array
        addTry(pos); // sets the next move as a tried move so it will not try again when backtracked here
        moves.enqueue(pos, moves.size()); //adds the new move to the stack
        setBeenThere(pos); //set that knight has been there
        setHistory(pos); //set move number of new move

        if (moves.full()) //when solution is found, stack will be full
            return true;
    }
    return false; //default case, no solution
}

coord qBoard::backtrack()
{
    clearTry(moves.front()); //clears the tries the last deadend made, so when knight comes back, it can try all moves
    coord nogood;
    moves.dequeue(nogood); //dequeues the deadend move off stack
    setBeenThere(nogood); //unsets the deadend move square
    setHistory(nogood); //erase from history
    return nogood; //returns the deadend move for checkspots to ignore
}

bool qBoard::checkClosed() //checks if the start pos and ending pos are one move away, closed
{
    if(startpos+UPLEFT == moves.front())
        return true;
    if(startpos+UPRIGHT == moves.front())
        return true;
    if(startpos+RIGHTUP == moves.front())
        return true;
    if(startpos+RIGHTDOWN == moves.front())
        return true;
    if(startpos+DOWNRIGHT == moves.front())
        return true;
    if(startpos+DOWNLEFT == moves.front())
        return true;
    if(startpos+LEFTDOWN == moves.front())
        return true;
    if(startpos+LEFTUP == moves.front())
        return true;
    return false;
}

void qBoard::setStart(const coord &c)
{
    startpos = c;
}

void qBoard::setEnd(const coord &c)
{
    endpos = c;
}


void qBoard::chessNotation()
{
    //create in order stack of moves
    pQueue<coord,int> copy(moves);
    pQueue<coord,int> reversed(moves.size());
    coord front;
    //dequeue copy's moves and enqueuees into reversed to get moves with starting at front
    while(!copy.empty())
    {
        copy.dequeue(front);
        reversed.enqueue(front, reversed.size());
    }
    //chess notation
    while(!reversed.empty())
    {
        coord temp;
        reversed.dequeue(temp); //dequeues and then outputs chess notation
        char x = 'a' + temp.getX();
        char y = '1' + temp.getY();
        cout << 'N' << x << y << " "; //'N' for knight
    }
}

void qBoard::print()
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
//        cout << "   ";
//        for (int x=0; x<XDIM; ++x)
//        {
//            if(beenThere[x][y])
//                printf("%-3c", 'x');
//            else
//                cout << "-  ";
//        }
        cout << endl;
    }
}

ostream& operator<<(ostream &out, const qBoard &b) //chess notation
{
    //create in order stack of moves
    pQueue<coord,int> copy(b.moves);
    pQueue<coord,int> reversed(copy.size());
    coord front;
    //dequeue copy's moves and enqueuees into reversed to get moves with starting at front
    while(!copy.empty())
    {
        copy.dequeue(front);
        reversed.enqueue(front, reversed.size());
    }
    //chess notation
    coord temp;
    if(out == cout)
    {
        while(!reversed.empty())
        {
            reversed.dequeue(temp); //dequeues and then outputs chess notation
            char x = 'a' + temp.getX();
            char y = '1' + temp.getY();
            out << 'N' << x << y << " ";
        }
    }
    else
    {
        out << "With starting position" << b.startpos << " and Ending pos:" << b.endpos << endl;
        while(!reversed.empty())
        {
            reversed.dequeue(temp); //dequeues and then outputs chess notation
            char x = 'a' + temp.getX();
            char y = '1' + temp.getY();
            out << x << y; //no spaces between
        }
    }
    return out;
}
