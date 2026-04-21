#ifndef MAP_H
#define MAP_H

#include "Chunk.h"

class Map
{
private:
    static const int MAP_SIZE = 401;
    static const int CENTER   = 200;

    Chunk* map[MAP_SIZE][MAP_SIZE];
    int vPos;
    int hPos;

    void createChunkIfMissing();

public:
    Map();
    ~Map();

    void moveNorth();
    void moveSouth();
    void moveEast();
    void moveWest();
    void fly(int x, int y);
    Chunk *getChunk();
};

#endif