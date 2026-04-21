#include "Map.h"
#include <cstdio>
#include <cstdlib>

Map::Map()
{
    vPos = CENTER;
    hPos = CENTER;

    for (int r = 0; r < MAP_SIZE; ++r)
        for (int c = 0; c < MAP_SIZE; ++c)
            map[r][c] = nullptr;

    createChunkIfMissing();
}

Map::~Map()
{
    for (int r = 0; r < MAP_SIZE; ++r)
        for (int c = 0; c < MAP_SIZE; ++c)
            delete map[r][c];
}

void Map::createChunkIfMissing()
{
    if (map[vPos][hPos]) return;

    int n = -1, s = -1, w = -1, e = -1;

    if (vPos > 0 && map[vPos - 1][hPos])
        n = map[vPos - 1][hPos]->getSGate();

    if (vPos < MAP_SIZE - 1 && map[vPos + 1][hPos])
        s = map[vPos + 1][hPos]->getNGate();

    if (hPos > 0 && map[vPos][hPos - 1])
        w = map[vPos][hPos - 1]->getEGate();

    if (hPos < MAP_SIZE - 1 && map[vPos][hPos + 1])
        e = map[vPos][hPos + 1]->getWGate();

    map[vPos][hPos] = new Chunk(vPos, hPos, n, s, w, e);
}

void Map::moveNorth()
{
    if (vPos <= 0)
    {
        
        return;
    }
    --vPos;
    createChunkIfMissing();
    
}

void Map::moveSouth()
{
    if (vPos >= MAP_SIZE - 1)
    {
        
        return;
    }
    ++vPos;
    createChunkIfMissing();
    
}

void Map::moveEast()
{
    if (hPos >= MAP_SIZE - 1)
    {
        
        return;
    }
    ++hPos;
    createChunkIfMissing();
    
}

void Map::moveWest()
{
    if (hPos <= 0)
    {
        
        return;
    }
    --hPos;
    createChunkIfMissing();
    
}

void Map::fly(int x, int y)
{
    hPos = x + CENTER;
    vPos = y + CENTER;
    createChunkIfMissing();
}

Chunk *Map::getChunk(){
    return map[vPos][hPos];
}