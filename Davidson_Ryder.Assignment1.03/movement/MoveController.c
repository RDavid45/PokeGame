#include "MoveController.h"
#include <limits.h>
#include <stdlib.h>

#define INF 100000

int moveCompare(const void *v1, const void *v2){
    const Move *m1 = (const Move*) v1;
    const Move *m2 = (const Move*) v2;

    int diff = m1->when - m2->when;
    if (diff == 0){
        if (m2->c->t == Trainer){
            return -1;
        }
        return 1;
    }
    return diff;
}

int initMoveController(MoveController *moves, Board *b, MovementCosts *mc, CharacterMap *cmap){
    moves->b = b;
    moves->h = malloc(sizeof(Heap));
    initHeap(moves->h, moveCompare, sizeof(Move));
    moves->costs = mc;
    moves->cmap = cmap;
    return 0;
}

int scheduleMove(MoveController *moves, Move *m){
    return heapAdd(moves->h, m);
}

int scheduleNextMove(MoveController *moves, Move *m){
    Character *ch = m->c;
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
    int minChange;
    int min = INF;
    switch (ch->npct){
        case HikerLogic:
            for (int i= 0; i< 8; i++){
                if (moves->costs->hiker[ch->vPos + dr[i]][ch->hPos + dc[i]].cost < min){
                    min = moves->costs->hiker[ch->vPos + dr[i]][ch->hPos + dc[i]].cost;
                    minChange = i;
                }
            }
            m->dx = dc[minChange];
            m->dy = dr[minChange];
            m->when += moves->costs->hiker[ch->vPos + dr[minChange]][ch->hPos + dc[minChange]].weight;
            break;
        case RivalLogic:
            for (int i= 0; i< 8; i++){
                if (moves->costs->rival[ch->vPos + dr[i]][ch->hPos + dc[i]].cost < min){
                    min = moves->costs->rival[ch->vPos + dr[i]][ch->hPos + dc[i]].cost;
                    minChange = i;
                }
            }
            m->dx = dc[minChange];
            m->dy = dr[minChange];
            m->when += moves->costs->rival[ch->vPos + dr[minChange]][ch->hPos + dc[minChange]].weight;
            break;
        case SwimmerLogic:
            minChange = rand() % 8;
            while (moves->b->board[ch->vPos + dr[minChange]][ch->hPos + dc[minChange]] != '~'){
                minChange = rand() % 8;
            }
            m->dx = dc[minChange];
            m->dy = dr[minChange];
            m->when += 7;
            break;
        case SentinalLogic:
            m->dx = 0;
            m->dy = 0;
            m->when += INF;
            break;
        case WandererLogic:
            char terrain = moves->b->board[ch->vPos][ch->hPos];
            if (moves->b->board[ch->vPos + m->dy][ch->hPos + m->dx] == terrain){
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                } else {
                    minChange = rand() % 8;
                    while (moves->b->board[ch->vPos + dr[minChange]][ch->hPos + dc[minChange]] != terrain){
                        minChange = rand() % 8;
                    }
                    m->dx = dc[minChange];
                    m->dy = dr[minChange];
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                }
            break;
        case ExplorerLogic:
            if (moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight != INF){
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                } else {
                    minChange = rand() % 8;
                    while (moves->costs->other[ch->vPos + dr[minChange]][ch->hPos + dc[minChange]].weight 
                        == INF){
                        minChange = rand() % 8;
                    }
                    m->dx = dc[minChange];
                    m->dy = dr[minChange];
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                }
            break;
        case PacerLogic:
            if (moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight != INF){
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                } else {
                    m->dx *= -1;
                    m->dy *= -1;
                    m->when += moves->costs->other[ch->vPos + m->dy][ch->hPos + m->dx].weight;
                }
            break;
        default:
            return -1;
    }
    return scheduleMove(moves, m);
}

static inline int inBounds(int r, int c) {
    return r > 0 && r < 20 && c > 0 && c < 79;
}

static inline int destWeightFor(const MoveController *mq, const Character *ch, int row, int col) {
    switch (ch->t) {
        case Hiker:  return mq->costs->hiker[row][col].weight;
        case Rival:  return mq->costs->rival[row][col].weight;
        case Trainer:return mq->costs->trainer[row][col].weight;
        default:     return mq->costs->other[row][col].weight;
    }
}

int handleMove(MoveController *moves, Move *m) {
    Character *ch = m->c;


    int nRow = ch->vPos + m->dy;
    int nCol = ch->hPos + m->dx;

   
    if (!inBounds(nRow, nCol)) {
        return -1;
    }

    
    if (moves->cmap->cmap[nRow][nCol] != NULL) {
        return -1;
    }

    int w = destWeightFor(moves, ch, nRow, nCol);
    if (w >= INF) {
        return -1;
    }

    if (moves->cmap->cmap[ch->vPos][ch->hPos] == ch && moves->cmap->cmap[nRow][nCol] == NULL) {
        moves->cmap->cmap[ch->vPos][ch->hPos] = NULL;
        moves->cmap->cmap[nRow][nCol] = ch;
    }
    

    ch->vPos = nRow;
    ch->hPos = nCol;

    if (ch->npct != TrainerLogic){
        scheduleNextMove(moves, m);
    }


    return 0;
}


int updateBoard(MoveController *moves, Board *b){
    if (!b){
        return -1;
    }
    moves->b = b;
    return 0;
}

