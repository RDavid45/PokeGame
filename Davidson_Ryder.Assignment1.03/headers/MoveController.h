#include "Character.h"
#include "CharacterMap.h"
#include "Movement.h"
#include "Board.h"
#include "Heap.h"

#ifndef MoveController_H
#define MoveController_H

typedef struct moves{
    Character *c;
    int dy;
    int dx;
    int when;
} Move;

typedef struct MoveController {
    Board *b;
    MovementCosts *costs;
    Heap *h;
    CharacterMap *cmap;
} MoveController;

int moveCompare(const void *v1, const void *v2);

int scheduleMove(MoveController *moves, Move *m);

int initMoveController(MoveController *moves, Board *b, MovementCosts *mc, CharacterMap *cmap);

int handleMove(MoveController *mq, Move *m);

int updateBoard(MoveController *moves, Board *b);



#endif