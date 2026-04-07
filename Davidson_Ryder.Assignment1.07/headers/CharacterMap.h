#pragma once

#include "Character.h"
#include "Board.h"

class MoveController;

struct SpawnResult {
    int requested;        // how many we attempted to spawn
    int placed;           // how many were actually placed
    int failed_attempts;  // how many positions we rejected
};

class CharacterMap {
public:

    CharacterMap();
    ~CharacterMap();

    int placeCharacter(Character* c, int vPos, int hPos);


    Character* at(int r, int c) const;

private:
    Character* cmap[Board::HEIGHT][Board::WIDTH];

};