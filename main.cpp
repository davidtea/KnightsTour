#include <iostream>
#include <fstream>
#include "board.h"

using namespace std;

void start();
void generateTours(int xdim, int ydim);

int main()
{
    cout << "Using Stack" << endl;
//    generateTours(8,8);
    start();
    return 0;
}

void generateTours(int xdim, int ydim)
{
    Board chess(xdim, ydim);
    ofstream myfile;
    myfile.open("ClosedTours.txt");
    if (myfile.is_open())
    {
        chess.generateClosedTours(myfile);
        myfile.close();
    }
    else
        cout <<"ERROR OPENING FILE" <<endl;
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
            cout << "Please enter your desired dimensions. (Must be greater than 3x3)" << endl;
            cout << "X: ";
            cin >> x;
            cout << "Y: ";
            cin >> y;
            if(x < 3 || y < 3)
                cout << "Please try again" << endl;
        } while(x < 3 || y < 3);
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
        double time;
        if(chess.calculateMoves(start, end))
        {
            time = (double)(clock() - tstart)/CLOCKS_PER_SEC;
            if(x <= 20 && y <= 20)
            {
                chess.print();
                cout << chess << endl;
            }
            else
                cout << "Dimensions are too big to display..." << endl;
            chess.checkClosed() ? cout << "This tour is closed" << endl : cout << "This tour is open" << endl;
        }
        else
        {
            time = (double)(clock() - tstart)/CLOCKS_PER_SEC;
            cout << "\nNo Solution\n";
        }
        cout << "Time taken: " << time << " seconds" << endl;
        cout << "Do you want to try another? (Y/N): ";
        cin >> choice;
        cout << endl;
    }
    cout << "Thank you for using this program." << endl;
}
