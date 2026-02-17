#include "Movement.h"


#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct Character{
    char icon;
    type t;
    int vPos;
    int hPos;
} Character;

int initCharacter(Character *c, char icon, type t);
int placeCharacter(Character *c, int hPos, int vPos);
int move(Character *c, char direction);
int getvPos(Character *c);
int gethPos(Character *c);

#endif