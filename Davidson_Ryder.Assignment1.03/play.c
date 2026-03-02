#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Movement.h"
#include "Character.h"
#include "CharacterMap.h"
#include "MoveController.h"

void showGameState(Map *m, CharacterMap *cmap);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Map m;
    initMap(&m);
    char dir;
    MovementCosts c;
    CharacterMap cmap;
    MoveController mq;
    initCharacterMap(&cmap);
    initCosts(&c, m.map[m.vPos][m.hPos]);
    initMoveController(&mq, m.map[m.vPos][m.hPos], &c, &cmap);
    Character pc;
    initCharacter(&pc, '@', Trainer, Trainer);
    placeCharacter(&cmap, &pc, m.map[m.vPos][m.hPos]->centerX, m.map[m.vPos][m.hPos]->centerY);
    Move move = {.c = &pc, .dx = 0, .dy = 0, .when = 100000};
    scheduleMove(&mq, &move);
    if (argc > 1){
        spawnNPCs(&cmap, &mq, m.map[m.vPos][m.hPos], &c, atoi(argv[1]));
    } else {
        spawnNPCs(&cmap, &mq, m.map[m.vPos][m.hPos], &c, 10);
    }
    while (1) {
        if (HeapSize(mq.h) == 0) break;
        heapPop(mq.h, &move);
        handleMove(&mq, &move);
        showGameState(&m, &cmap);
        usleep(250000);
    }
    while (1) {
        
        updateCosts(&c, m.map[m.vPos][m.hPos], pc.vPos, pc.hPos);
        printf("what do you want to do [n,e,s,w,f,q]: ");
        scanf(" %c", &dir);
        
        
        switch (dir)
        {
        case 'n':
            moveNorth(&m);
	    system("clear");
            break;
        case 's':
            moveSouth(&m);
	    system("clear");
            break;
        case 'e':
            moveEast(&m);
	    system("clear");
            break;
        case 'w':
            moveWest(&m);
	    system("clear");
            break;
        case 'f':
            int x, y;
            printf("where do you want to move (x y): ");
            scanf(" %d %d", &x, &y);
            if (x > 200 || x < -200 || y > 200 || y < -200){
                system("clear");
                printf("Invalid cordinates. must be between -200-200 \n");
                break;
            }
            fly(&m, x, y);
	    system("clear");
            break;
        case 'q':
            printf("Quitting\n");
            destroyMap(&m);
	    system("clear");
            return 0;
        default:
	    system("clear");
            printf("invalid input, please use [n,e,s,w,f,q] \n");
            break;
        }
    }

}

void showGameState(Map *m, CharacterMap *cmap){
    Board *b = m->map[m->vPos][m->hPos];
    printf("Current pos (%d, %d)\n", m->hPos - 200, m->vPos -200);
    for (int i = 0;i < b->height;i++){
        for (int j = 0; j<b->width; j++){
            if (cmap->cmap[i][j]){
                printf("\033[91m%c\033[0m", cmap->cmap[i][j]->icon);
            } else if (b->board[i][j] == '%'){
                printf("\033[90m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == '~'){
                printf("\033[34m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == ':'){
                printf("\033[32m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == '.'){
                printf("\033[92m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == '^'){
                printf("\033[38;2;34;139;34m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == 'm'){
                printf("\033[36m%c\033[0m", b->board[i][j]);
            } else if (b->board[i][j] == 'c'){
                printf("\033[38;2;255;200;100m%c\033[0m", b->board[i][j]);
            } else {
                printf("%c", b->board[i][j]);
            }
        }
        printf("\n");
    }
}

