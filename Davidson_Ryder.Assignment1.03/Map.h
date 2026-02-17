#include "Board.h"

#ifndef MAP_H
#define MAP_H

typedef struct Map 
{
    Board *map[401][401];
    int vPos;
    int hPos;
} Map;

int initMap(Map *m);
int printScreen(Map *m);
int moveNorth(Map *m);
int moveSouth(Map *m);
int moveEast(Map *m);
int moveWest(Map *m);
int fly(Map *m, int x, int y);

int destroyMap(Map *m);



#endif
