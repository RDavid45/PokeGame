#include "Colors.h"
#include <ncurses.h>
#include <cstdlib>
#include <cstdio>

namespace Colors {

static short s255(int x) {
    return static_cast<short>((x * 1000) / 255);
}

void initTerminal()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    if (!has_colors()) {
        endwin();
        std::fprintf(stderr, "Your terminal does not support colors.\n");
        std::exit(1);
    }

    start_color();
    use_default_colors();

    bool can_custom = can_change_color();

    short FOREST_ID = 8;
    short SAND_ID = 9;
    short GRAY_ID = 10;
    short LIGHTGREEN_ID = 11;

    if (can_custom) {
        init_color(FOREST_ID, s255(34), s255(139), s255(34));
        init_color(SAND_ID, s255(255), s255(200), s255(100));
        init_color(GRAY_ID, s255(128), s255(128), s255(128));
        init_color(LIGHTGREEN_ID, s255(20), s255(200), s255(60));
    } else {
        FOREST_ID = COLOR_GREEN;
        SAND_ID = COLOR_YELLOW;
        GRAY_ID = COLOR_WHITE;
        LIGHTGREEN_ID = COLOR_GREEN;
    }

    short BG = -1;

    init_pair(CHARACTER, COLOR_RED, BG);
    init_pair(ROCK, GRAY_ID, BG);
    init_pair(WATER, COLOR_BLUE, BG);
    init_pair(TGRASS, COLOR_GREEN, BG);
    init_pair(SGRASS, LIGHTGREEN_ID, BG);
    init_pair(FOREST, FOREST_ID, BG);
    init_pair(MART, COLOR_CYAN, BG);
    init_pair(CENTER, SAND_ID, BG);
}

} // namespace Colors