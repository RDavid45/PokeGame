#include "Character.h"


int inbounds(int row, int col){
    return (row >= 0 && row <= 20 && col >= 0 && col <= 79);
}

int initCharacter(Character *c, char icon, characterType npct, type t){
    c->icon = icon;
    c->t = t;
    c->npct = npct;
    return 0;
}


int getvPos(Character *c){
    return c->vPos;
}

int gethPos(Character *c){
    return c->hPos;
}