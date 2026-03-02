#include "Movement.h"


#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum characterType {
    Hiker = 0x01,
    Rival = 0x02,
    Swimmer = 0x04,
    Trainer = 0x08,
    Wanderer = 0x10,
    Sentinal = 0x20,
    Explorer = 0x40,
    Pacer = 0x80,
} characterType;

typedef struct Character{
    char icon;
    characterType npct;
    type t;
    int vPos;
    int hPos;
} Character;

int initCharacter(Character *c, char icon, characterType npct, type t);
int getvPos(Character *c);
int gethPos(Character *c);

#endif