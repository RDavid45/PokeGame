#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Movement.h"
#include "Character.h"
#include "CharacterMap.h"
#include "MoveController.h"
#include <assert.h>
#include <string.h>
#include <ncurses.h>
#include "Colors.h"


void showGameState(Map *m, CharacterMap *cmap);
void handleCenter();
void handleShowTrainers(Character *pc, CharacterMap *cmap);

int main(int argc, char *argv[]){
    srand(time(NULL));
    Map m;
    initMap(&m);
    MovementCosts c;
    CharacterMap cmap;
    MoveController mq;
    initCharacterMap(&cmap);
    initCosts(&c, m.map[m.vPos][m.hPos]);
    initMoveController(&mq, m.map[m.vPos][m.hPos], &c, &cmap);
    assert(mq.h != NULL);
    Character pc;
    initCharacter(&pc, '@', TrainerLogic, Trainer);
    placeCharacter(&cmap, &pc, m.map[m.vPos][m.hPos]->centerX, m.map[m.vPos][m.hPos]->centerY);
    Move move = {.c = &pc, .dx = 1, .dy = 1, .when = 0};
    scheduleMove(&mq, &move);
    int npcs = -1;
    for (int i = 0; i < argc - 1; i++){
        if (strcmp(argv[i], "--numtrainers") == 0 && i + 1 < argc){
            npcs = atoi(argv[i + 1]);
            break;
        }
    }
    if (npcs > -1){
        spawnNPCs(&cmap, &mq, m.map[m.vPos][m.hPos], npcs);
    } else {
        spawnNPCs(&cmap, &mq, m.map[m.vPos][m.hPos], 10);
    }
    updateCosts(&c, m.map[m.vPos][m.hPos], pc.vPos, pc.hPos);
    initTerminal();
    Board *current = m.map[m.vPos][m.hPos];

    uint32_t running, invalid;
    int32_t key;
    running = invalid = 1;
    showGameState(&m, &cmap);
    while (running) {
        invalid = 1;
        if (heapEmpty(mq.h)) break;
        heapPop(mq.h, &move);
        handleMove(&mq, &move);
        showGameState(&m, &cmap);
        if (move.c->t == Trainer){
            while (invalid){
                key =getch();
                switch (key) {
                case 'y': {
                    move.dx = -1;
                    move.dy = -1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'k': {
                    move.dx = 0;
                    move.dy = -1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'u': {
                    move.dx = +1;
                    move.dy = -1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'l': {
                    move.dx = +1;
                    move.dy = 0;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'n': {
                    move.dx = +1;
                    move.dy = +1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'j': {
                    move.dx = 0;
                    move.dy = +1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'b': {
                    move.dx = -1;
                    move.dy = +1;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case 'h': {
                    move.dx = -1;
                    move.dy = 0;
                    if (c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight < 100){    
                        move.when += c.trainer[pc.vPos + move.dy][pc.hPos + move.dx].weight;
                        scheduleMove(&mq, &move);
                        invalid =0;
                    }
                    break;
                    }
                case KEY_RIGHT: {
                    if (current->board[pc.vPos][pc.hPos] == 'c'){
                        handleCenter();
                        showGameState(&m, &cmap);
                    }
                    break;
                    }
                case '.': {
                    move.dx = 0;
                    move.dy = 0;
                    move.when += c.trainer[pc.vPos][pc.hPos].weight;
                    scheduleMove(&mq, &move);
                    invalid =0;
                    break;
                    }
                case 't': {
                    handleShowTrainers(&pc, &cmap);
                    showGameState(&m, &cmap);
                    break;
                    }
                case 'Q': {
                    running = 0;
                    invalid = 0;
                    break;
                    }
                default: {
                    mvprintw(0, 0,"invalid input               ");
                    break;
                    }   
                }
            }
        }
    /*
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
    */
    }
    
}

void handleCenter(){
    clear();
    mvprintw(0, 0, "%s", "Welcome to the Pokemon Center, press left to leave");
    int32_t key;
    while (1){
        key = getch();
        switch (key)
        {
        case KEY_LEFT:
            return;
        default:
            break;
        }
    }
}

void printTrainerInfo(Character *pc, Character *npc){
    int pch = pc->hPos;
    int pcv = pc->vPos;
    int dh = npc->hPos - pch;
    int dv = npc->vPos - pcv;
    char str[80];
    str[0] = '\0';

    int mag_v = (dv <= 0) ? -dv : dv;
    int mag_h = (dh <= 0) ? -dh : dh;

    snprintf(str + strlen(str), sizeof(str) - strlen(str),
         "%c %d %s, ", npc->icon, mag_v, (dv <= 0) ? "north" : "south");
    snprintf(str + strlen(str), sizeof(str) - strlen(str),
         "%d %s", mag_h, (dh <= 0) ? "west" : "east");
    addstr(str);
}

int min(int i, int j){
    if (i < j){return i;}
    return j;
}


void handleShowTrainers(Character *pc, CharacterMap *cmap) {
    int active = 1;
    int key;

    int title_row = 0;
    int list_start_row = 1;

    ArrayList trainers;
    ArrayListinit(&trainers, sizeof(Character*)); 

    int numTrainers = 0;
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            if (cmap->cmap[i][j] && cmap->cmap[i][j]->npct != TrainerLogic) {
                Character *ptr = cmap->cmap[i][j];
                ArrayListadd(&trainers, &ptr);      
                numTrainers++;
            }
        }
    }

    int startAt = 0;

    int rows = getmaxy(stdscr);
    int visible_rows = rows - list_start_row; 
    if (visible_rows < 0) visible_rows = 0;


    void render(void) {
        erase();
        mvprintw(title_row, 0, "%s", "Trainers, press ESC to quit");

        int to_show = min(visible_rows, numTrainers - startAt);
        for (int i = 0; i < to_show; i++) {
            Character *npc = NULL;
            ArrayListget(&trainers, &npc, startAt + i); 
            move(list_start_row + i, 0);
            printTrainerInfo(pc, npc);
        }
        refresh();
    };

    render();

    while (active) {
        key = getch();
        switch (key) {
            case KEY_UP:
                if (startAt > 0) {
                    startAt--;
                    render();
                }
                break;

            case KEY_DOWN:
                if (numTrainers - startAt > visible_rows) {
                    startAt++;
                    render();
                }
                break;

            case 27: /* ESC */
                active = 0;
                break;

            default:
                break;
        }
    }

    ArrayListdestroy(&trainers);
}



void showGameState(Map *m, CharacterMap *cmap)
{
    Board *b = m->map[m->vPos][m->hPos];

    clear();

    mvprintw(0, 0, "Current pos (%d, %d)", m->hPos - 200, m->vPos - 200);

    int start_row = 1;
    int start_col = 0;


    int drawable_rows = b->height;
    int drawable_cols = b->width;

    for (int i = 0; i < drawable_rows; i++) {
        move(start_row + i, start_col);
        for (int j = 0; j < drawable_cols; j++) {
            char ch;
            short pair = 0;
            attr_t attrs = A_NORMAL;

            if (cmap->cmap[i][j]) {
                ch = cmap->cmap[i][j]->icon;
                pair = PAIR_CHARACTER;
                attrs |= A_BOLD;
            } else {
                ch = b->board[i][j];
                switch (ch) {
                    case '%': pair = PAIR_ROCK; break;     
                    case '~': pair = PAIR_WATER; break;    
                    case ':': pair = PAIR_TGRASS; break;   
                    case '.':
                        pair = PAIR_SGRASS;                  
                        attrs |= A_BOLD;                   
                        break;
                    case '^': pair = PAIR_FOREST; break;   
                    case 'm': pair = PAIR_MART; break; 
                    case 'c': pair = PAIR_CENTER; break;     
                    default:
                        pair = 0;                          
                        break;
                }
            }

            if (pair != 0) attron(COLOR_PAIR(pair) | attrs);
            addch((chtype)ch);
            if (pair != 0) attroff(COLOR_PAIR(pair) | attrs);
        }
    }

    refresh();
}


/*
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
*/

