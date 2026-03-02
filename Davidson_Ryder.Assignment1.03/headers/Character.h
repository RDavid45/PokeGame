#include "Movement.h"


#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum characterType {
    HikerLogic = 0x01,
    RivalLogic = 0x02,
    SwimmerLogic = 0x04,
    TrainerLogic = 0x08,
    WandererLogic = 0x10,
    SentinalLogic = 0x20,
    ExplorerLogic = 0x40,
    PacerLogic = 0x80,
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