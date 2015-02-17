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
        do {
            cout << "Please enter your desired dimensions. (Must be greater than 5x5)" << endl;
            cout << "X: ";
            cin >> x;
            cout << "Y: ";
            cin >> y;
            if(x < 5 || y < 5)
                cout << "Please try again" << endl;
        } while(x < 5 || y < 5);
        do {
            cout << "Now please enter your starting position." << endl;
            cin >> start;
            if(start.getX() < 0 || start.getX() >= x || start.getY() < 0 || start.getY() >= y)
                cout << "Invalid square, please enter one that exists." << endl;
        } while(start.getX() < 0 || start.getX() >= x || start.getY() < 0 || start.getY() >= y);
        do
        {
            cout << "Now please enter your ending position.\n(If it doesn't matter, enter same as starting)" << endl;
            cin >> end;
            if(end.getX() < 0 || end.getX() >= x || end.getY() < 0 || end.getY() >= y)
                cout << "Invalid square, please enter one that exists." << endl;
        } while(end.getX() < 0 || end.getX() >= x || end.getY() < 0 || end.getY() >= y);
        clock_t tstart = clock();
        Board chess(x,y);
        if(chess.calculateMoves(start, end))
        {
            chess.print();
            cout << chess << endl;
            chess.checkClosed() ? cout << "This tour is closed" << endl : cout << "This tour is open" << endl;
        }
        else
        {
            chess.print();
            cout << "\nNo Solution\n";
        };
        cout << "Time taken: " << (double)(clock() - tstart)/CLOCKS_PER_SEC << " seconds" << endl;
        cout << "Do you want to try another? (Y/N): ";
        cin >> choice;
    }
}
