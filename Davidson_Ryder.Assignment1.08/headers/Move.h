#ifndef MOVE_H
#define MOVE_H

#include "Comparable.h"
#include "Character.h"

class Move : public Comparable<Move>
{
public:
    Character* c;
    int dy;
    int dx;
    int when;

    Move();
    Move(Character* ch, int dy, int dx, int when);

    int compareTo(const Move other) const override;
};

#endif