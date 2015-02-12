#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    Board chess;
    chess.calculateMoves(coord(0,0));

    return 0;
}

