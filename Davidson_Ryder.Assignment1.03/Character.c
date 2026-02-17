#include "Character.h"


int inbounds(int row, int col){
    return (row >= 0 && row <= 20 && col >= 0 && col <= 79);
}

int initCharacter(Character *c, char icon, type t){
    c->icon = icon;
    c->t = t;
}

int placeCharacter(Character *c, int hPos, int vPos){
    if (inbounds(vPos, hPos)){
        c->hPos = hPos;
        c->vPos = vPos;
        return 0;
    }
    return -1;
}

int move(Character *c, char direction){
    switch (direction)
    {
    case 'n':
        if (inbounds(c->vPos -1, c->hPos)){
            c->vPos--;
            return 0;
        }
        return -1;
    case 's':
        if (inbounds(c->vPos +1, c->hPos)){
            c->vPos++;
            return 0;
        }
        return -1;
    case 'w':
        if (inbounds(c->vPos, c->hPos -1)){
            c->hPos--;
            return 0;
        }
        return -1;
    case 'e':
        if (inbounds(c->vPos, c->hPos + 1)){
            c->hPos++;
            return 0;
        }
        return -1;
    
    default:
        return -1;
    }
}

int getvPos(Character *c){
    return c->vPos;
}

int gethPos(Character *c){
    return c->hPos;
}