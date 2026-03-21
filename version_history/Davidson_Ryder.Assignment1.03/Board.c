#include "Board.h"
#include "seedQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

int initBoard(Board *b)
{   
    b->height = 21;
    b->width = 80;
    for(int i = 0;i < b->height;i++){
        for(int j = 0;j<b->width;j++){
            if (i==0 || i == 20){
                b->board[i][j] = '-';
            } else if (j == 0 || j == 79){
                b->board[i][j] = '|';
            } else {
                b->board[i][j] = ' ';
            }
        }
    }
    b->board[0][0] = '/';
    b->board[20][0] = '\\';
    b->board[20][79] = '/';
    b->board[0][79] = '\\';
    b->top = rand() % 78 + 1;
    b->bottom = rand() % 78 + 1;
    b->right = rand() % 19 + 1;
    b->left = rand() % 19 + 1;
    return 0;
}
int genTerrain(Board *b)
{
    struct SeedQueue q;
    int dx;
    int dy;
    char c;
    initSeedQueue(&q);
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, ':');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, '~');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, ':');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, '.');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, ':');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, '.');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, '^');
    dx = rand() % 80; dy = rand() % 21;
    enqueueSeed(&q, dx, dy, '%');
    while(!isEmptyQueue(&q)){
        dequeueSeed(&q, &dx, &dy, &c);
        if(dx > 77){
            dx = 77;
        }
        if(dx <2){
            dx =2;
        }
        if(dy > 18){
            dy = 18;
        }
        if(dy < 2){
            dy = 2;
        }
        if(b->board[dy+1][dx] == ' '){
            b->board[dy+1][dx] = c;
            enqueueSeed(&q, dx, dy+1, c);
        }
        if(b->board[dy-1][dx] == ' '){
            b->board[dy-1][dx] = c;
            enqueueSeed(&q, dx, dy-1, c);
        }
        if(b->board[dy][dx+1] == ' '){
            b->board[dy][dx+1] = c;
            enqueueSeed(&q, dx+1, dy, c);
        }
        if(b->board[dy][dx-1] == ' '){
            b->board[dy][dx-1] = c;
            enqueueSeed(&q, dx-1, dy, c);
        }
        if(b->board[dy+2][dx] == ' '){
            b->board[dy+2][dx] = c;
            enqueueSeed(&q, dx, dy+2, c);
        }
        if(b->board[dy-2][dx] == ' '){
            b->board[dy-2][dx] = c;
            enqueueSeed(&q, dx, dy-2, c);
        }
        if(b->board[dy][dx+2] == ' '){
            b->board[dy][dx+2] = c;
            enqueueSeed(&q, dx+2, dy, c);
        }
        if(b->board[dy][dx-2] == ' '){
            b->board[dy][dx-2] = c;
            enqueueSeed(&q, dx-2, dy, c);
        }
        if(b->board[dy+1][dx] == ' '){
            b->board[dy+1][dx] = c;
            enqueueSeed(&q, dx+1, dy+1, c);
        }
        if(b->board[dy-1][dx] == ' '){
            b->board[dy-1][dx] = c;
            enqueueSeed(&q, dx+1, dy-1, c);
        }
        if(b->board[dy][dx+1] == ' '){
            b->board[dy][dx+1] = c;
            enqueueSeed(&q, dx-1, dy-1, c);
        }
        if(b->board[dy][dx-1] == ' '){
            b->board[dy][dx-1] = c;
            enqueueSeed(&q, dx-1, dy+1, c);
        }
    }
    b->board[1][1] = b->board[1][2];
    b->board[1][78] = b->board[1][77];
    b->board[19][78] = b->board[19][77];
    b->board[19][1] = b->board[19][2];
    return 0;
}
int buildroads(Board *b, int hPos, int vPos)
{
    int x1;
    int x2;
    int y1;
    int y2;
    x1 = b->bottom;
    x2 = b->top;
    y1 = b->right;
    y2 = b->left;

    b->centerX = rand() % (65 - 21) + 21;
    b->centerY = rand() % (16 - 5) + 5;
    b->board[b->centerY][b->centerX] = '#';
    int i, j;
    if (hPos < 400) {
        b->board[y1][79] = '#';
        i = 78; j = y1;
        b->board[j][i] = '#';
        while(i != b->centerX || j != b->centerY){
            if (abs(b->centerX - i) > abs(b->centerY - j)){
                i += (b->centerX > i) ? 1 : -1;
            } else {
                j += (b->centerY > j) ? 1 : -1;
            }
            b->board[j][i] = '#';
        }
    }
    if (hPos > 0) {
        b->board[y2][0] = '#';
        i = 1; j = y2;
        b->board[j][i] = '#';
        while(i != b->centerX || j != b->centerY){
            if (abs(b->centerX - i) > abs(b->centerY - j)){
                i += (b->centerX > i) ? 1 : -1;
            } else {
                j += (b->centerY > j) ? 1 : -1;
            }
            b->board[j][i] = '#';
        }
    }
    if (vPos < 400) {
        b->board[20][x1] = '#';
        i = x1; j = 19;
        b->board[j][i] = '#';
        while(i != b->centerX || j != b->centerY){
            if (abs(b->centerX - i) > abs(b->centerY - j)){
                i += (b->centerX > i) ? 1 : -1;
            } else {
                j += (b->centerY > j) ? 1 : -1;
            }
            b->board[j][i] = '#';
        }
    }
    if (vPos > 0) {
        b->board[0][x2] = '#';
        i = x2; j = 1;
        b->board[j][i] = '#';
        while(i != b->centerX || j != b->centerY){
            if (abs(b->centerX - i) > abs(b->centerY - j)){
                i += (b->centerX > i) ? 1 : -1;
            } else {
                j += (b->centerY > j) ? 1 : -1;
            }
            b->board[j][i] = '#';
        }
    }
    return 0;
}

int inBounds2x2(Board *b, int x, int y, int dx, int dy)
{    
    return (x  > 0 && x  < b->width-1  &&
            dx > 0 && dx < b->width-1  &&
            y  > 0 && y  < b->height-1 &&
            dy > 0 && dy < b->height-1);
}

static int isBlocked(char tile)
{
    // Blocks roads and existing buildings
    return (tile == '#' || tile == 'c' || tile == 'm');
}

int canPlace2x2(Board *b, int x, int y, int dx, int dy)
{
    if (!inBounds2x2(b, x, y, dx, dy)) {
        return 0;
    }

    // check if all tiles are not blocked
    return (!isBlocked(b->board[y][x])  &&
            !isBlocked(b->board[y][dx]) &&
            !isBlocked(b->board[dy][x]) &&
            !isBlocked(b->board[dy][dx]));
}

int placeMart(Board *b, int x, int y)
{
    int t = -1, bo = -1, l = -1, r = -1;

    if (canPlace2x2(b, x-2, y,   x-1, y-1)) {
        t = y-1; bo = y;   l = x-2; r = x-1;
    } else if (canPlace2x2(b, x-2, y,   x-1, y+1)) {
        t = y;   bo = y+1; l = x-2; r = x-1;
    } else if (canPlace2x2(b, x-1, y-2, x,   y-1)) {
        t = y-2; bo = y-1; l = x-1; r = x;
    } else if (canPlace2x2(b, x,   y-2, x+1, y-1)) {
        t = y-2; bo = y-1; l = x;   r = x+1;
    } else if (canPlace2x2(b, x+1, y,   x+2, y-1)) {
        t = y-1; bo = y;   l = x+1; r = x+2;
    } else if (canPlace2x2(b, x+1, y,   x+2, y+1)) {
        t = y;   bo = y+1; l = x+1; r = x+2;
    } else if (canPlace2x2(b, x,   y+1, x+1, y+2)) {
        t = y+1; bo = y+2; l = x;   r = x+1;
    } else if (canPlace2x2(b, x-1, y+1, x,   y+2)) {
        t = y+1; bo = y+2; l = x-1; r = x;
    } else {
        // No valid placement found
        return -1;
    }

    b->board[t][l]  = 'm';
    b->board[t][r]  = 'm';
    b->board[bo][l] = 'm';
    b->board[bo][r] = 'm';

    return 0;
}

int placeCenter(Board *b, int x, int y)
{
    int t = -1, bo = -1, l = -1, r = -1;

    if (canPlace2x2(b, x-2, y,   x-1, y-1)) {
        t = y-1; bo = y;   l = x-2; r = x-1;
    } else if (canPlace2x2(b, x-2, y,   x-1, y+1)) {
        t = y;   bo = y+1; l = x-2; r = x-1;
    } else if (canPlace2x2(b, x-1, y-2, x,   y-1)) {
        t = y-2; bo = y-1; l = x-1; r = x;
    } else if (canPlace2x2(b, x,   y-2, x+1, y-1)) {
        t = y-2; bo = y-1; l = x;   r = x+1;
    } else if (canPlace2x2(b, x+1, y,   x+2, y-1)) {
        t = y-1; bo = y;   l = x+1; r = x+2;
    } else if (canPlace2x2(b, x+1, y,   x+2, y+1)) {
        t = y;   bo = y+1; l = x+1; r = x+2;
    } else if (canPlace2x2(b, x,   y+1, x+1, y+2)) {
        t = y+1; bo = y+2; l = x;   r = x+1;
    } else if (canPlace2x2(b, x-1, y+1, x,   y+2)) {
        t = y+1; bo = y+2; l = x-1; r = x;
    } else {
        return -1;
    }

    b->board[t][l]  = 'c';
    b->board[t][r]  = 'c';
    b->board[bo][l] = 'c';
    b->board[bo][r] = 'c';

    return 0;
}

int placeBuildings(Map *m)
{
    Board *b = m->map[m->vPos][m->hPos];
    int x = rand() % 74 + 3;
    int y = rand() % 15 + 3;
    int md = abs(m->hPos - 200) + abs(m->vPos - 200);
    md = (md < 200) ? md : 200;
    if (rand() % 100 <= (-45*md/200)+50 || (m->hPos == 200 && m->vPos ==200)){
        for (int i = 0; i < 80; i++){
            if (b->board[y][i] == '#'){
                if(!placeCenter(b, i, y)){
                    break;
                }
            }
        }
    }
    if (rand() % 100 <= (-45*md/200)+50 || (m->hPos == 200 && m->vPos ==200)){
        for (int j = 0; j < 21; j++){
            if (b->board[j][x] == '#'){
                if(!placeMart(b, x, j)){
                    break;
                }
            }
        }
    }
    return 0;
}


int genBoard(Map *m)
{
    Board *b = m->map[m->vPos][m->hPos];
    initBoard(b);
    Board *bn = (m->vPos > 0) ? m->map[m->vPos-1][m->hPos] : NULL;
    Board *bs = (m->vPos < 400) ? m->map[m->vPos+1][m->hPos] : NULL;
    Board *bw = (m->hPos > 0) ? m->map[m->vPos][m->hPos-1] : NULL;
    Board *be = (m->hPos < 400) ? m->map[m->vPos][m->hPos+1] : NULL;
    if (bn){
        b->top = bn->bottom;
    } if (bs){
        b->bottom = bs->top;
    } if (bw){
        b->left =  bw->right;
    } if (be) {
        b->right = be->left;
    }
    genTerrain(b);
    buildroads(b, m->hPos, m->vPos);
    placeBuildings(m);
    if (m->vPos == 400){
        b->board[20][b->bottom] = '%';
    }if (m->vPos == 0){
        b->board[0][b->bottom] = '%';
    }if (m->hPos == 400){
        b->board[b->right][79] = '%';
    }if (m->hPos == 0){
        b->board[b->left][0] = '%';
    }

    return 0;
}

int printBoard(Board *b)
{
    for (int i = 0;i < b->height;i++){
        for (int j = 0; j<b->width; j++){
            
            if (b->board[i][j] == '%'){
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
    return 0;
}