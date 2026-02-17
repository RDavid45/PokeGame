#ifndef BOARD_H
#define BOARD_H

typedef struct Map Map;

typedef struct Board 
{
    char board[21][80];
    int height;
    int width;
    int centerX;
    int centerY;
    int left;
    int top;
    int right;
    int bottom;
} Board;

/**
 * Generates a terrain, roads, and buildings buildings for the current tile of @p m.
 * If there already exists boards around the current tile it will connect the gates to them.
 * 
 * @param m the world map
 * 
 * @note This function does not validate that @p item is non-NULL; passing NULL
 *       may cause damage. Make sure @p item is valid. It is recomended you 
 *       do not call this method directly and instead use the Map movement functions.
 */
int genBoard(Map *m);

/**
 * prints the board @p b to the screen.
 * 
 * @param b the board to be printed
 * 
 * @note This function does not validate that @p b is non-NULL; passing NULL
 *       may cause damage. Make sure @p b is valid.
 */
int printBoard(Board *b);


#endif
