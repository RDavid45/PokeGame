#include "CharacterMap.h"
#include <stdlib.h>
#include "MoveController.h"
#include "Movement.h"

#ifndef INF
#define INF 100000
#endif
 

int initCharacterMap(CharacterMap *c){
    for (int i = 0; i < 21; i++){
        for (int j = 0; j < 80; j++){
            c->cmap[i][j] = NULL;
        }
    }
    return 0;
}

int placeCharacter(CharacterMap *map, Character *c, int hPos, int vPos){
    c->hPos = hPos;
    c->vPos = vPos;
    map->cmap[vPos][hPos] = c;
    return 0;
}

static inline char iconFor(characterType t) {
    switch (t) {
        case HikerLogic:    return 'h';
        case RivalLogic:    return 'r';
        case PacerLogic:    return 'p';
        case WandererLogic: return 'w';
        case SentinalLogic: return 's';
        case ExplorerLogic: return 'e';
        default:       return '?';
    }
}

static characterType randomBehavior(void) {
    static const characterType pool[6] = { HikerLogic, RivalLogic, PacerLogic, WandererLogic, SentinalLogic, ExplorerLogic };
    return pool[rand() % 6];
}

static type costCategoryFor(characterType t) {
    switch (t) {
        case HikerLogic: return Hiker;
        case RivalLogic: return Rival;
        default:    return Other; 
    }
}

static int inBounds(int r, int c) { return (r > 0 && r < 20 && c > 0 && c < 79);}

static int isOccupied(const CharacterMap *cmap,int r, int c) {return cmap->cmap[r][c] != NULL;}

static int canSpawn(const CharacterMap *cm, Board *b, const MovementCosts *mc, type npc, int r, int c) {
    if (isOccupied(cm, r, c)) return 0;
    if (findCost(b->board[r][c], npc) >= INF) return 0;
    return 1;
}


SpawnResult spawnNPCs(CharacterMap *cmap, MoveController *mq, Board *b, MovementCosts *mc, int count){
    SpawnResult sr = { .requested = count, .placed = 0, .failed_attempts = 0 };

    int max_attempts = count * 50;
    while (sr.placed < count && sr.failed_attempts < max_attempts) {
            characterType npc = randomBehavior();
            type cc = costCategoryFor(npc);
            int r = (rand() % 19) + 1;  
            int c = (rand() % 78) + 1;  
        if (sr.placed == 0){
            npc = RivalLogic;
            cc = costCategoryFor(npc);  
        } else if (sr.placed == 1){
            npc = HikerLogic;
            cc = costCategoryFor(npc);   
        } else {
            npc = randomBehavior();
            cc = costCategoryFor(npc); 
        }
        if (!canSpawn(cmap, b, mc, cc, r, c)) { sr.failed_attempts++; continue; }

        Character *ch = (Character*)malloc(sizeof(*ch));
        if (!ch) break;
        char icon = iconFor(npc);
       
        initCharacter(ch, icon, npc, cc);
        placeCharacter(cmap, ch, c, r);  // (hPos, vPos)

        Move m = {0};
        m.c = ch;
        m.when = 0;
        scheduleMove(mq, &m);

        sr.placed++;
    }

    return sr;
}
