#include <iostream>
#include "board.h"

using namespace std;

void start();

int main()
{
//    Board chess(8,4);
//    chess.calculateMoves(coord(0,0));
    start();

    return 0;
}


void start()
{
    int x, y;
    coord start, end;
    char choice;
    while(toupper(choice) != 'N')
    {
        cout << "Knight's Tour Program." << endl;
        cout << "Please enter your desired dimensions." << endl;
        cout << "X: ";
        cin >> x;
        cout << "Y: ";
        cin >> y;
        cout << "Now please enter your starting position." << endl;
        cin >> start;
        cout << "Now please enter your ending position." << endl;
        cin >> end;
        clock_t tstart = clock();
        Board chess(x,y);
        chess.calculateMoves(start, end);
        chess.print();
        chess.chessNotation();
        cout << endl;
        chess.checkClosed() ? cout << "This tour is closed" << endl : cout << "This tour is open" << endl;
        cout << "Time taken: " << (double)(clock() - tstart)/CLOCKS_PER_SEC << " seconds" << endl;
        cout << "Do you want to try another? (Y/N): ";
        cin >> choice;
    }
}
