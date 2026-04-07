#include "Move.h"

Move::Move() : c(nullptr), dy(0), dx(0), when(0) {}
    
Move::Move(Character* ch, int dy, int dx, int when)
    : c(ch), dy(dy), dx(dx), when(when) {}

int Move::compareTo(const Move other) const{
    int diff = when - other.when;
    if (diff == 0) {
        if (other.c->getType() == Type::Trainer)
            return -1;
        return 1;
    }
    return diff;
}