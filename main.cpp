#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    Board chess(8,4);
    chess.calculateMoves(coord(0,0));

    return 0;
}

