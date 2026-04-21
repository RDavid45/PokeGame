#ifndef MOVECONTROLLER_H
#define MOVECONTROLLER_H

#include "Board.h"
#include "Movement.h"
#include "Character.h"
#include "CharacterMap.h"
#include "Heap.h"
#include "Move.h"

class MoveController
{
public:
    MoveController(Board& b,
                   MovementCosts& mc,
                   CharacterMap& cmap,
                   int dist);
    ~MoveController();

    int scheduleMove(const Move& m);
    int handleMove(Move& m);
    Move getNextMove();

private:
    // ================= Core State =================
    Board& b;
    MovementCosts& costs;
    CharacterMap& cmap;
    Heap<Move>* heap;
    int dist;

    // ================= Movement Helpers =================
    static inline bool inBounds(int r, int c);
    int scheduleNextMove(Move& m);
    int findNextDirection(int r, int c) const;

    Mon* getRandomMon();
};

#endif