#include "Map.h"
#include <stdio.h>
#include <stdlib.h>

int initMap(Map *m){
    m->hPos = 200;
    m->vPos = 200;
    
    for (int r = 0; r < 401; r++) {
        for (int c = 0; c < 401; c++) {
            m->map[r][c] = NULL;
        }
    }

    Board *temp;
    if(!((temp = malloc(sizeof (*temp))))){
        return -1;
    }
    m->map[m->vPos][m->hPos] = temp;
    genBoard(m);
    return 0;
}

int moveNorth(Map *m)
{
    if (m->vPos <= 0){
        printf("You are at the world boarder! \n");
        return -1;
    }
    m->vPos--;
    if (!(m->map[m->vPos][m->hPos])){
        Board *temp;
        if(!((temp = malloc(sizeof (*temp))))){
        return -1;
        }
        m->map[m->vPos][m->hPos] = temp;
        genBoard(m);
    }
    //printf("DEBUG indices v=%d h=%d\n", m->vPos, m->hPos);
    return 0;
}
int moveSouth(Map *m)
{
    if (m->vPos >= 400){
        printf("You are at the world boarder! \n");
        return -1;
    }
    m->vPos++;
    if (!(m->map[m->vPos][m->hPos])){
        Board *temp;
        if(!((temp = malloc(sizeof (*temp))))){
        return -1;
        }
        m->map[m->vPos][m->hPos] = temp;
        genBoard(m);
    }
    //printf("DEBUG indices v=%d h=%d\n", m->vPos, m->hPos);
    return 0;
}
int moveEast(Map *m)
{
    if (m->hPos == 400){
        printf("You are at the world boarder! \n");
        return -1;
    }
    m->hPos++;
    if (!(m->map[m->vPos][m->hPos])){
        Board *temp;
        if(!((temp = malloc(sizeof (*temp))))){
        return -1;
        }
        m->map[m->vPos][m->hPos] = temp;
        genBoard(m);
    }
    //printf("DEBUG indices v=%d h=%d\n", m->vPos, m->hPos);
    return 0;
}
int moveWest(Map *m)
{
    if (m->vPos <= 0){
        printf("You are at the world boarder! \n");
        return -1;
    }
    m->hPos--;
    if (!(m->map[m->vPos][m->hPos])){
        Board *temp;
        if(!((temp = malloc(sizeof (*temp))))){
        return -1;
        }
        m->map[m->vPos][m->hPos] = temp;
        genBoard(m);
    }
    //printf("DEBUG indices v=%d h=%d\n", m->vPos, m->hPos);
    return 0;
}
int fly(Map *m, int x, int y)
{
    m->hPos = x + 200;
    m->vPos = y + 200;
    if (!(m->map[m->vPos][m->hPos])){
        Board *temp;
        if(!((temp = malloc(sizeof (*temp))))){
        return -1;
        }
        m->map[m->vPos][m->hPos] = temp;
        genBoard(m);
    }
    //printf("DEBUG indices v=%d h=%d\n", m->vPos, m->hPos);
    return 0;
}

int printScreen(Map *m)
{
    printf("Current pos (%d, %d)\n", m->hPos - 200, m->vPos -200);
    printBoard(m->map[m->vPos][m->hPos]);
	return 0;    
}

int destroyMap(Map *m){
    int i, j;
    for (i = 0; i < 401; i++){
        for(j = 0; j<401; j++){
            if (m->map[i][j]){
                free(m->map[i][j]);
            }
        }
    }
    return 0;
}
