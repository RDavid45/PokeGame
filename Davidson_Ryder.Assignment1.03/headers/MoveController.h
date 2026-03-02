#include "Character.h"
#include "CharacterMap.h"
#include "Movement.h"
#include "Board.h"
#include "Heap.h"

#ifndef MOVEQUEUE_H
#define MOVEQUEUE_H

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
} MoveQueue;

int moveCompare(const void *v1, const void *v2);

int scheduleMove(MoveQueue *moves, Move *m);

int initMoveQueue(MoveQueue *moves, Board *b, MovementCosts *mc, CharacterMap *cmap);

int handleMove(MoveQueue *mq, Move *m);

int updateBoard(MoveQueue *moves, Board *b);



#endif