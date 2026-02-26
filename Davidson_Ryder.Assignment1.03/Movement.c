#include "Movement.h"
#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

#define INF 1000000

typedef struct costNode {
    int row;
    int col;
    int cost;
} costNode;

int findCost(char c, type t);
void resetCosts(MovementCosts *c, const Board *b);
int costsCompare(const void *c1, const void *c2);
int checkValidPos(int row, int col);


int InitCosts(MovementCosts *c, const Board *b)
{
    resetCosts(c, b);
    return 0;
}

void hikerCosts(MovementCosts *c, int row, int col)
{

    Heap h;
    initHeap(&h, costsCompare, sizeof (costNode));
    costNode p;
    p.row = row;
    p.col = col;
    p.cost = 0;
    heapAdd(&h , &p);
    
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!heapEmpty(&h))
    {
        costNode u;
        heapPop(&h, &u);

        if (u.cost >= c->hiker[u.row][u.col].cost){
            continue;
        }
        c->hiker[u.row][u.col].cost = u.cost;

        costNode v;
        for (int i = 0; i < 8; i++) {
            if (checkValidPos(u.row + dr[i], u.col + dc[i])){
                v.row = u.row + dr[i];
                v.col = u.col + dc[i];
                v.cost = u.cost + c->hiker[v.row][v.col].weight;
                if (v.cost < c->hiker[v.row][v.col].cost){
                    heapAdd(&h, &v);
                }
            }
        }

       
           
    }
    heapDestroy(&h);
    
}

void rivalCosts(MovementCosts *c, int row, int col)
{
    Heap h;
    initHeap(&h, costsCompare, sizeof (costNode));
    costNode p;
    p.row = row;
    p.col = col;
    p.cost = 0;
    heapAdd(&h , &p);
    
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!heapEmpty(&h))
    {
        costNode u;
        heapPop(&h, &u);

        if (u.cost >= c->rival[u.row][u.col].cost){
            continue;
        }
        c->rival[u.row][u.col].cost = u.cost;

        costNode v;
        for (int i = 0; i < 8; i++) {
            if (checkValidPos(u.row + dr[i], u.col + dc[i])){
                v.row = u.row + dr[i];
                v.col = u.col + dc[i];
                v.cost = u.cost + c->rival[v.row][v.col].weight;
                if (v.cost < c->rival[v.row][v.col].cost){
                    heapAdd(&h, &v);
                }
            }
        }

       
           
    }
    heapDestroy(&h);
    
}

void trainerCosts(MovementCosts *c, int row, int col)
{
    Heap h;
    initHeap(&h, costsCompare, sizeof (costNode));
    costNode p;
    p.row = row;
    p.col = col;
    p.cost = 0;
    heapAdd(&h , &p);
    
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!heapEmpty(&h))
    {
        costNode u;
        heapPop(&h, &u);

        if (u.cost >= c->trainer[u.row][u.col].cost){
            continue;
        }
        c->trainer[u.row][u.col].cost = u.cost;

        costNode v;
        for (int i = 0; i < 8; i++) {
            if (checkValidPos(u.row + dr[i], u.col + dc[i])){
                v.row = u.row + dr[i];
                v.col = u.col + dc[i];
                v.cost = u.cost + c->trainer[v.row][v.col].weight;
                if (v.cost < c->trainer[v.row][v.col].cost){
                    heapAdd(&h, &v);
                }
            }
        }

       
           
    }
    heapDestroy(&h);
    
}

void swimmerCosts(MovementCosts *c, int row, int col)
{

    Heap h;
    initHeap(&h, costsCompare, sizeof (costNode));
    costNode p;
    p.row = row;
    p.col = col;
    p.cost = 0;
    heapAdd(&h , &p);
    
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!heapEmpty(&h))
    {
        costNode u;
        heapPop(&h, &u);

        if (u.cost >= c->swimmer[u.row][u.col].cost){
            continue;
        }
        c->swimmer[u.row][u.col].cost = u.cost;

        costNode v;
        for (int i = 0; i < 8; i++) {
            if (checkValidPos(u.row + dr[i], u.col + dc[i])){
                v.row = u.row + dr[i];
                v.col = u.col + dc[i];
                v.cost = u.cost + c->swimmer[v.row][v.col].weight;
                if (v.cost < c->swimmer[v.row][v.col].cost){
                    heapAdd(&h, &v);
                }
            }
        }

       
           
    }
    heapDestroy(&h);
    
}

void otherCosts(MovementCosts *c, int row, int col)
{

    Heap h;
    initHeap(&h, costsCompare, sizeof (costNode));
    costNode p;
    p.row = row;
    p.col = col;
    p.cost = 0;
    heapAdd(&h , &p);
    
    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!heapEmpty(&h))
    {
        costNode u;
        heapPop(&h, &u);

        if (u.cost >= c->other[u.row][u.col].cost){
            continue;
        }
        c->other[u.row][u.col].cost = u.cost;

        costNode v;
        for (int i = 0; i < 8; i++) {
            if (checkValidPos(u.row + dr[i], u.col + dc[i])){
                v.row = u.row + dr[i];
                v.col = u.col + dc[i];
                v.cost = u.cost + c->other[v.row][v.col].weight;
                if (v.cost < c->other[v.row][v.col].cost){
                    heapAdd(&h, &v);
                }
            }
        }

       
           
    }
    heapDestroy(&h);
    
}

void resetCosts(MovementCosts *c, const Board *b){
    for (int i =0; i < 21; i++){
        for (int j=0; j<80; j++){
            
            // set row pos for each cost
            c->hiker[i][j].row = i;
            c->rival[i][j].row = i;
            c->other[i][j].row = i;
            c->trainer[i][j].row = i;
            c->swimmer[i][j].row = i;

            // set col pos for each cost
            c->hiker[i][j].col = j;
            c->rival[i][j].col = j;
            c->trainer[i][j].col = j;
            c->swimmer[i][j].col = j;
            c->other[i][j].col = j;

            // set cost to INF
            c->hiker[i][j].cost = INF;
            c->rival[i][j].cost = INF;
            c->trainer[i][j].cost = INF;
            c->swimmer[i][j].cost = INF;
            c->other[i][j].cost = INF;

            // set weights
            c->hiker[i][j].weight = findCost(b->board[i][j], Hiker);
            c->rival[i][j].weight = findCost(b->board[i][j], Rival);
            c->trainer[i][j].weight = findCost(b->board[i][j], Trainer);
            c->swimmer[i][j].weight = findCost(b->board[i][j], Swimmer);
            c->other[i][j].weight = findCost(b->board[i][j], Other);
            
        }
    }
}

void updateCosts(MovementCosts *c, const Board *b, int row, int col)
{
    resetCosts(c, b);
    hikerCosts(c, row, col);
    rivalCosts(c, row, col);
    swimmerCosts(c, row, col);
    trainerCosts(c, row, col);
    otherCosts(c, row, col);
}

int findCost(char c, type t)
{
    if (t == Hiker){
        switch (c){
            case '%':
                return 15;
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 15;
            case '^':
                return 15;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    }else if (t == Rival){
        switch (c) {
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 20;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    } else if (t == Swimmer){
        switch (c) {
            case '~':
                return 7;
            default:
                return INF;
        }
    } else {
        switch (c) {
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 20;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    }
    return INF;
}

int costsCompare(const void *c1, const void *c2)
{
    const costNode *x = (const costNode *)c1;
    const costNode *y = (const costNode *)c2;
    return x->cost - y->cost;
}

int checkValidPos(int row, int col){
    return (row > 0 && row < 20 && col > 0 && col < 79);
}

void printCosts(MovementCosts *c)
{
    for(int i =0; i < 21; i++){
        for (int j = 0; j<80; j++){
            if (c->hiker[i][j].cost < 1000000){
                printf("%3d", c->hiker[i][j].cost % 100);
            } else {
                printf(" --");
            }
        }
        printf("\n");
    }
    for(int i =0; i < 21; i++){
        for (int j = 0; j<80; j++){
            if (c->rival[i][j].cost < 1000000){
                printf("%3d", c->rival[i][j].cost % 100);
            } else {
                printf(" --");
            }
        }
        printf("\n");
    }
}