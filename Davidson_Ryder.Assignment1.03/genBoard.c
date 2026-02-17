#include <stdio.h>
#include "Board.h"

int main(int argc, char *argv[])
{
    Board b;
    genBoard(&b);
    printBoard(&b);

    return 0;
}