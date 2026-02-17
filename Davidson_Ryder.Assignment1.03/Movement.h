#include "Board.h"

#ifndef MOVEMENT_H
#define MOVEMENT_H

typedef enum type {
    Hiker,
    Rival,
    Trainer,
    Swimmer,
    Other
}type;

typedef struct cost{
    int cost;
    int weight;
    int row;
    int col;
} cost;

typedef struct costs{
    cost hiker[21][80];
    cost rival[21][80];
} MovementCosts;

int InitCosts(MovementCosts *c, const Board *b);
void updateCosts(MovementCosts *c, const Board *b, int row, int col);
void hikerCosts(MovementCosts *c, int row, int col);
void rivalCosts(MovementCosts *c, int row, int col);
void printCosts(MovementCosts *c);


#endif