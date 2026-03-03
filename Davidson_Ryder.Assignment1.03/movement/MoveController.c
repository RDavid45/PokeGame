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

static inline int inBounds(int r, int c) {
    return r > 0 && r < 20 && c > 0 && c < 79;
}

int findNextDirection(const MoveController *moves, int r, int c) {
    static const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    static const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
    int candidates[8], cnt = 0;
    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k]; int nc = c + dc[k];
        if (!inBounds(nr, nc)) continue;
        if (moves->costs->other[nr][nc].weight > 100) continue;
        candidates[cnt++] = k;
    }
    if (cnt > 0) {
        return candidates[rand() % cnt];
    } else {
        return -1;
    }

}

int scheduleNextMove(MoveController *moves, Move *m) {
    Character *ch = m->c;
    static const int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    static const int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    int r = ch->vPos;
    int c = ch->hPos;

    #define STALL() do { m->dx = 0; m->dy = 0; m->when += 10; } while (0)

    switch (ch->npct) {
        case HikerLogic: {
            int bestI = -1;
            int bestCost = INF;
            int start = rand() % 8;

            for (int k = 0; k < 8; k++) {
                int i  = (start + k) & 7;
                int nr = r + dr[i], nc = c + dc[i];
                if (!inBounds(nr, nc)) continue;
                if (moves->cmap->cmap[nr][nc] != NULL) continue;
                int cost   = moves->costs->hiker[nr][nc].cost;
                int weight = moves->costs->hiker[nr][nc].weight;
                if (weight >= INF || cost >= INF) continue;
                if (cost < bestCost) { bestCost = cost; bestI = i; }
            }

            int hereCost = moves->costs->hiker[r][c].cost;

            if (bestI >= 0 && bestCost < hereCost) {
                m->dx = dc[bestI];
                m->dy = dr[bestI];
                m->when += moves->costs->hiker[r + m->dy][c + m->dx].weight;
            } else {
                // 2)any same-cost valid neighbor?
                int candidates[8], cnt = 0;
                for (int k = 0; k < 8; k++) {
                    int i  = (start + k) & 7;
                    int nr = r + dr[i], nc = c + dc[i];
                    if (!inBounds(nr, nc)) continue;
                    if (moves->cmap->cmap[nr][nc] != NULL) continue;
                    int cost   = moves->costs->hiker[nr][nc].cost;
                    int weight = moves->costs->hiker[nr][nc].weight;
                    if (weight >= INF || cost >= INF) continue;
                    if (cost == hereCost) candidates[cnt++] = i;
                }
                if (cnt > 0) {
                    int i = candidates[rand() % cnt];
                    m->dx = dc[i]; m->dy = dr[i];
                    m->when += moves->costs->hiker[r + m->dy][c + m->dx].weight;
                } else {
                    STALL();
                }
            }
            break;
        }

        case RivalLogic: {
            int bestI = -1;
            int bestCost = INF;
            int start = rand() % 8;

            for (int k = 0; k < 8; ++k) {
                int i  = (start + k) & 7;
                int nr = r + dr[i], nc = c + dc[i];
                if (!inBounds(nr, nc)) continue;
                if (moves->cmap->cmap[nr][nc] != NULL) continue;
                int cost   = moves->costs->rival[nr][nc].cost;
                int weight = moves->costs->rival[nr][nc].weight;
                if (weight >= INF || cost >= INF) continue;
                if (cost < bestCost) { bestCost = cost; bestI = i; }
            }

            int hereCost = moves->costs->rival[r][c].cost;

            if (bestI >= 0 && bestCost < hereCost) {
                m->dx = dc[bestI];
                m->dy = dr[bestI];
                m->when += moves->costs->rival[r + m->dy][c + m->dx].weight;
            } else {
                // 2) same cost as current
                int candidates[8], cnt = 0;
                for (int k = 0; k < 8; k++) {
                    int i  = (start + k) & 7;
                    int nr = r + dr[i], nc = c + dc[i];
                    if (!inBounds(nr, nc)) continue;
                    if (moves->cmap->cmap[nr][nc] != NULL) continue;
                    int cost   = moves->costs->rival[nr][nc].cost;
                    int weight = moves->costs->rival[nr][nc].weight;
                    if (weight >= INF || cost >= INF) continue;
                    if (cost == hereCost) candidates[cnt++] = i;
                }
                if (cnt > 0) {
                    int i = candidates[rand() % cnt];
                    m->dx = dc[i]; m->dy = dr[i];
                    m->when += moves->costs->rival[r + m->dy][c + m->dx].weight;
                } else {
                    STALL();
                }
            }
            break;
        }
        case SentinalLogic:
            m->dx = 0;
            m->dy = 0;
            m->when += INF;
            break;

        case WandererLogic: {
            // Stay on the same terrain if possible; otherwise pick another tile of that terrain.
            char terrain = moves->b->board[r][c];
            int nr = r + m->dy, nc = c + m->dx;
            int can_continue = inBounds(nr, nc) && 
                        //moves->cmap->cmap[nr][nc] == NULL &&
                        moves->b->board[nr][nc] == terrain && moves->costs->other[nr][nc].weight < 100;

            if (nr == r && nc == c) {
                can_continue = 0;
            }

            if (!can_continue) {
                int i = findNextDirection(moves, r, c);
                while (i >= 0 && moves->b->board[r + dr[i]][c + dc[i]] != terrain) {
                    i = findNextDirection(moves, r, c);
                }
                if ((i = findNextDirection(moves, r, c)) >= 0) {
                    m->dx = dc[i]; m->dy = dr[i];    
                } else {
                    STALL();
                    break;
                }
            }
            m->when += moves->costs->other[r + m->dy][c + m->dx].weight;
            break;
        }

        case ExplorerLogic: {

            int nr = r + m->dy, nc = c + m->dx;
            int can_continue = inBounds(nr, nc) &&
                        //moves->cmap->cmap[nr][nc] == NULL &&
                        moves->costs->other[nr][nc].weight < 100;

            if (nr == r && nc == c) {
                can_continue = 0;
            }

            if (!can_continue) {
                int i = findNextDirection(moves, r, c);

                if (i >= 0) {
                    nr = r + dr[i]; nc = c + dc[i];
                    m->dx = dc[i]; m->dy = dr[i];
                } else {
                    STALL();
                    break;
                }
            }
            m->when += moves->costs->other[nr][nc].weight;
            break;
        }

        case PacerLogic: {
            // Try forward; if blocked, reverse; if still blocked, stall.

            int nr = r + m->dy, nc = c + m->dx;

            if (nr == r && nc == c) {
                int i = findNextDirection(moves, r, c);
                if (i >= 0) {
                    m->dx = dc[i]; m->dy = dr[i];
                } else {
                    STALL();
                    break;
                }
            }

            if (!inBounds(nr, nc) || moves->costs->other[nr][nc].weight > 100) {
                m->dx = -m->dx;
                m->dy = -m->dy;
                nr = r + m->dy; nc = c + m->dx;
            }
            m->when += moves->costs->other[nr][nc].weight;
            if (m->when >= INF) {
                return -1;
            }
            break;
        }

        default:
            return -1;
    }

    return scheduleMove(moves, m);
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
        if (ch->npct != TrainerLogic){
        scheduleNextMove(moves, m);
        }
        return -1;
    }

    
    if (moves->cmap->cmap[nRow][nCol] != NULL) {
        if (ch->npct != TrainerLogic){
        scheduleNextMove(moves, m);
    }
        return -1;
    }

    int w = destWeightFor(moves, ch, nRow, nCol);
    if (w >= INF) {
        if (ch->npct != TrainerLogic){
        scheduleNextMove(moves, m);
        }
        return -1;
    }

    if (moves->cmap->cmap[ch->vPos][ch->hPos] == ch && moves->cmap->cmap[nRow][nCol] == NULL) {
        moves->cmap->cmap[ch->vPos][ch->hPos] = NULL;
        moves->cmap->cmap[nRow][nCol] = ch;
        ch->vPos = nRow;
        ch->hPos = nCol;
        if (ch->t == Trainer) {
            updateCosts(moves->costs, moves->b, nRow, nCol);
        }
    }
    

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

