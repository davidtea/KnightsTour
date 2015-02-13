#include <iostream>
#include "board.h"

using namespace std;

int main()
{
    Board chess(8,8);
    chess.calculateMoves(coord(1,0));

    return 0;
}

