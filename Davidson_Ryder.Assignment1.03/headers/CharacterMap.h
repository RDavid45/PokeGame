#include "Character.h"
#include "Board.h"

#ifndef CHARACTERMAP_H
#define CHARACTERMAP_H


typedef struct SpawnResult {
    int requested;       // how many we attempted to spawn
    int placed;          // how many were actually placed
    int failed_attempts; // how many positions we rejected
} SpawnResult;

typedef struct CharacterMap{
    Character *cmap[21][80];
} CharacterMap;

typedef struct MoveQueue MoveQueue;

int initCharacterMap(CharacterMap *c);

int placeCharacter(CharacterMap *cmap, Character *c, int hPos, int vPos);

SpawnResult spawnNPCs(CharacterMap *cmap, MoveQueue *mq, Board *b, MovementCosts *mc, int count);

#endif