#include "CharacterMap.h"
#include "MoveController.h"
#include "Movement.h"

#include <cstdlib>

#ifndef INF
#define INF 100000
#endif

CharacterMap::CharacterMap() {
    for (int i = 0; i < Board::HEIGHT; ++i) {
        for (int j = 0; j < Board::WIDTH; ++j) {
            cmap[i][j] = nullptr;
        }
    }
}
CharacterMap::~CharacterMap() = default;

int CharacterMap::placeCharacter(Character* c, int vPos, int hPos) {
    
    cmap[vPos][hPos] = c;
    if (c) {c->setPosition(vPos, hPos);}
    return 0;
}

Character* CharacterMap::at(int r, int c) const {
    return cmap[r][c];
}
