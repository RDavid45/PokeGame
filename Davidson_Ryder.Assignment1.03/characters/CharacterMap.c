#include "CharacterMap.h"
#include <stdlib.h>
#include "MoveController.h"

#ifndef INF
#define INF 100000
#endif
 

int initCharacterMap(CharacterMap *c){
    for (int i = 0; i < 21; i++){
        for (int j = 0; j < 80; j++){
            c->cmap[i][j] = NULL;
        }
    }
}

int placeCharacter(CharacterMap *map, Character *c, int hPos, int vPos){
    c->hPos = hPos;
    c->vPos = vPos;
    map->cmap[vPos][hPos] = c;
}

static inline char iconFor(characterType t) {
    switch (t) {
        case Hiker:    return 'h';
        case Rival:    return 'r';
        case Pacer:    return 'p';
        case Wanderer: return 'w';
        case Sentinal: return 's';
        case Explorer: return 'e';
        default:       return '?';
    }
}

static characterType randomBehavior(void) {
    static const characterType pool[6] = { Hiker, Rival, Pacer, Wanderer, Sentinal, Explorer };
    return pool[rand() % 6];
}

static type costCategoryFor(characterType npc) {
    switch (npc) {
        case Hiker: return Hiker;
        case Rival: return Rival;
        default:    return Other; 
    }
}

static int inBounds(int r, int c) { return (r > 0 && r < 20 && c > 0 && c < 79);}

static int isOccupied(CharacterMap *cmap,int r, int c) {return cmap->cmap[r][c] != NULL;}

static int canSpawn(const CharacterMap *cm, Board *b, const MovementCosts *mc, characterType npc, int r, int c) {
    if (isOccupied(cm, r, c)) return 0;
    if (weight_at(mc, npc, r, c) >= INF) return 0;
    return 1;
}

static void pickInitialDir(Board *b, const MovementCosts *mc, characterType npc, int r, int c, int *dx, int *dy) {
    static const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    static const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
    *dx = 0; *dy = 0;
    if (npc == Hiker || npc == Rival || npc == Sentinal) return; // decided later or doesn't move

    char spawn_terrain = b->board[r][c];
    for (int tries = 0; tries < 16; ++tries) {
        int i = rand() % 8;
        int nr = r + dr[i], nc = c + dc[i];
        if (!inBounds(nr, nc)) continue;
        if (npc == Wanderer && b->board[nr][nc] != spawn_terrain) continue;
        if (mc->other[nr][nc].weight >= INF) continue;
        *dx = dc[i]; *dy = dr[i];
        return;
    }
}

SpawnResult spawnNPCs(CharacterMap *cmap, MoveQueue *mq, Board *b, MovementCosts *mc, int count){
    SpawnResult sr = { .requested = count, .placed = 0, .failed_attempts = 0 };

    int max_attempts = count * 50;
    while (sr.placed < count && sr.failed_attempts < max_attempts) {
        characterType npc = randomBehavior();
        int r = (rand() % 19) + 1;  
        int c = (rand() % 78) + 1;  
        if (!canSpawn(cmap, b, mc, npc, r, c)) { sr.failed_attempts++; continue; }

        Character *ch = (Character*)malloc(sizeof(*ch));
        if (!ch) break;
        char icon = iconFor(npc);
        type cc = costCategoryFor(npc);
        initCharacter(ch, icon, npc, cc);
        placeCharacter(cmap, ch, c, r);  // (hPos, vPos)

        Move m = {0};
        m.c = ch;
        m.when = 0;
        pickInitialDir(b, mc, npc, r, c, &m.dx, &m.dy);
        scheduleNextMove(mq, &m);

        sr.placed++;
    }

    return sr;
}
