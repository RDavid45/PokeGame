#include <ncurses.h>
#include <stdlib.h>
#include "Colors.h"

static short s255(int x) { return (short)((x * 1000) / 255); }


void initTerminal(void){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    if (!has_colors()) {
        endwin();
        fprintf(stderr, "Your terminal does not support colors.\n");
        exit(1);
    }
    start_color();

    use_default_colors();

    bool can_custom = can_change_color();

    short FOREST_ID = 8;
    short SAND_ID   = 9;
    short GRAY_ID   = 10;
    short LIGHTGREEN_ID = 11; 

    if (can_custom) {
        // Forest green ~ rgb(34,139,34)
        init_color(FOREST_ID, s255(34), s255(139), s255(34));
        // Sand ~ rgb(255,120,100)
        init_color(SAND_ID,   s255(255), s255(200), s255(100));
        // Gray ~ rgb(128,128,128) for '%'
        init_color(GRAY_ID,   s255(128), s255(128), s255(128));
        // Light greed ~ rgb(20,200,60)
        init_color(LIGHTGREEN_ID, s255(20), s255(200), s255(60));
    } else {
        
        FOREST_ID = COLOR_GREEN; 
        SAND_ID   = COLOR_YELLOW;
        GRAY_ID   = COLOR_WHITE; 
        LIGHTGREEN_ID = COLOR_GREEN;
    }

    // Map color pairs 
    short BG = -1;

    init_pair(PAIR_CHARACTER, COLOR_RED, BG);

    init_pair(PAIR_ROCK, GRAY_ID, BG);

    init_pair(PAIR_WATER, COLOR_BLUE, BG);

    init_pair(PAIR_TGRASS, COLOR_GREEN, BG);

    init_pair(PAIR_SGRASS, LIGHTGREEN_ID, BG);

    init_pair(PAIR_FOREST, FOREST_ID, BG);

    init_pair(PAIR_MART, COLOR_CYAN, BG);

    init_pair(PAIR_CENTER, SAND_ID, BG);   
}