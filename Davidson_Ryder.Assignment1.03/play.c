#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Movement.h"
#include "Character.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Map m;
    initMap(&m);
    char dir;
    MovementCosts c;
    InitCosts(&c, m.map[m.vPos][m.hPos]);
    Character pc;
    initCharacter(&pc, '@', Trainer);
    while (1) {
        placeCharacter(&pc, m.map[m.vPos][m.hPos]->centerX, m.map[m.vPos][m.hPos]->centerY);
        updateCosts(&c, m.map[m.vPos][m.hPos], 10, 10);
        printScreen(&m, &pc);
        printCosts(&c);
        printf("what do you want to do [n,e,s,w,f,q]: ");
        scanf(" %c", &dir);
        
        
        switch (dir)
        {
        case 'n':
            moveNorth(&m);
	    system("clear");
            break;
        case 's':
            moveSouth(&m);
	    system("clear");
            break;
        case 'e':
            moveEast(&m);
	    system("clear");
            break;
        case 'w':
            moveWest(&m);
	    system("clear");
            break;
        case 'f':
            int x, y;
            printf("where do you want to move (x y): ");
            scanf(" %d %d", &x, &y);
            if (x > 200 || x < -200 || y > 200 || y < -200){
                system("clear");
                printf("Invalid cordinates. must be between -200-200 \n");
                break;
            }
            fly(&m, x, y);
	    system("clear");
            break;
        case 'q':
            printf("Quitting\n");
            destroyMap(&m);
	    system("clear");
            return 0;
        default:
	    system("clear");
            printf("invalid input, please use [n,e,s,w,f,q] \n");
            break;
        }
    }
}
