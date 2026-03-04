#include "Movement.h"


#ifndef CHARACTER_H
#define CHARACTER_H

typedef enum characterType {
    HikerLogic = 0x01,
    RivalLogic = 0x02,
    TrainerLogic = 0x04,
    WandererLogic = 0x08,
    SentinalLogic = 0x10,
    ExplorerLogic = 0x20,
    PacerLogic = 0x40,
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