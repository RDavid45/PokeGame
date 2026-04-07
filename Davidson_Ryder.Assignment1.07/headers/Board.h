#pragma once

#include "SeedQueue.h"


class Board
{
public:
    static constexpr int HEIGHT = 21;
    static constexpr int WIDTH  = 80;
    static constexpr int INF    = 1000000;

    Board(
        int v, int h,
        int north,
        int south,
        int west,
        int east
);
    ~Board();
    
    int getNGate() {return topGate;}
    int getEGate() {return rightGate;}
    int getSGate() {return bottomGate;}
    int getWGate() {return leftGate;}

    int getCenterX() const { return centerX; }
    int getCenterY() const { return centerY; }

    char getTerrainAT(int r, int c) const;


    /**/


private:
    /* ========= TERRAIN ========= */
    char terrain[HEIGHT][WIDTH];
    int vPos;
    int hPos;
    int centerX;
    int centerY;
    int leftGate;
    int topGate;
    int rightGate;
    int bottomGate;

    
    void generate(int north,
        int south,
        int west,
        int east);  
    void initBordersAndGates();
    void genTerrain();
    void buildRoads();
    void placeBuildings();

    //-----------helpers-------------// 
    bool inBounds(int r, int c) const;
    bool placeCenter(int x, int y);
    bool placeMart(int x, int y);
    bool canPlace2x2(int x, int y, int dx, int dy)const;
    bool inBounds2x2(int x, int y, int dx, int dy)const;
    bool isBlocked(char tile)const;
};