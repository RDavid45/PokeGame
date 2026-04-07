#include "Board.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>


Board::Board(
        int v, int h,
        int north,
        int south,
        int west,
        int east
)
    : vPos(v), hPos(h)
{
    generate(north, south, west, east);  // create terrain first
}

Board::~Board() = default;

void Board::generate(int north,
        int south,
        int west,
        int east)
{    
    if (north >= 0){
        topGate = north;
    }else { topGate = rand() % 78 + 1; } 
    if (south  >= 0){
        bottomGate = south;
    } else { bottomGate = rand() % 78 + 1; }
    if (west  >= 0){
        leftGate = west;
    } else { leftGate = rand() % 19 + 1; }
    if (east  >= 0) {
        rightGate = east;
    } else { rightGate = rand() % 19 + 1; }
    initBordersAndGates();
    genTerrain();
    buildRoads();
    placeBuildings();
    if (vPos == 400){
        terrain[20][bottomGate] = '-';
    }if (vPos == 0){
        terrain[0][topGate] = '-';
    }if (hPos == 400){
        terrain[rightGate][79] = '|';
    }if (hPos == 0){
        terrain[leftGate][0] = '|';
    }
}

void Board::initBordersAndGates() {
    for(int i = 0;i < HEIGHT; i++){
        for(int j = 0;j < WIDTH; j++){
            if (i==0 || i == 20){
                terrain[i][j] = '-';
            } else if (j == 0 || j == 79){
                terrain[i][j] = '|';
            } else {
                terrain[i][j] = ' ';
            }
        }
    }
    terrain[0][0] = '/';
    terrain[20][0] = '\\';
    terrain[20][79] = '/';
    terrain[0][79] = '\\';
}

void Board::genTerrain()
{
    SeedQueue q;

    const char seeds[] = { ':', '~', ':', '.', ':', '.', '^', '%' };

    // enqueue initial seeds
    for (char c : seeds)
        q.enqueue(rand() % WIDTH, rand() % HEIGHT, c);

    while (!q.isEmpty())
    {
        auto* s = q.dequeue();
        
        auto inside = [](int x, int y) {
            return x >= 1 && x < WIDTH - 1 && y >= 1 && y < HEIGHT - 1;
        };
        int x = s->x;
        int y = s->y;
        char c = s->chr;

        static const int dirs[][2] = {
            {  1,  0 }, { -1,  0 }, {  0,  1 }, {  0, -1 },
            {  2,  0 }, { -2,  0 }, {  0,  2 }, {  0, -2 }//,
            /*{  1,  1 }, {  1, -1 }, { -1,  1 }, { -1, -1 }*/
        };

        for (auto& d : dirs)
        {
            int nx = x + d[0];
            int ny = y + d[1];

            if (inside(nx, ny) && terrain[ny][nx] == ' ') {
                terrain[ny][nx] = c;
                q.enqueue(nx, ny, c);
            }
        }
        delete s;
    }


    terrain[1][1]                    = terrain[1][2];
    terrain[1][WIDTH - 2]            = terrain[1][WIDTH - 3];
    terrain[HEIGHT - 2][1]           = terrain[HEIGHT - 2][2];
    terrain[HEIGHT - 2][WIDTH - 2]   = terrain[HEIGHT - 2][WIDTH - 3];
}

void Board::buildRoads()
{
    int x1;
    int x2;
    int y1;
    int y2;
    x1 = bottomGate;
    x2 = topGate;
    y1 = rightGate;
    y2 = leftGate;

    centerX = rand() % (65 - 21) + 21;
    centerY = rand() % (16 - 5) + 5;
    terrain[centerY][centerX] = '#';
    int i, j;
    if (hPos < 400) {
        terrain[y1][79] = '#';
        i = 78; j = y1;
        terrain[j][i] = '#';
        while(i != centerX || j != centerY){
            if (abs(centerX - i) > abs(centerY - j)){
                i += (centerX > i) ? 1 : -1;
            } else {
                j += (centerY > j) ? 1 : -1;
            }
            terrain[j][i] = '#';
        }
    }
    if (hPos > 0) {
        terrain[y2][0] = '#';
        i = 1; j = y2;
        terrain[j][i] = '#';
        while(i != centerX || j != centerY){
            if (abs(centerX - i) > abs(centerY - j)){
                i += (centerX > i) ? 1 : -1;
            } else {
                j += (centerY > j) ? 1 : -1;
            }
            terrain[j][i] = '#';
        }
    }
    if (vPos < 400) {
        terrain[20][x1] = '#';
        i = x1; j = 19;
        terrain[j][i] = '#';
        while(i != centerX || j != centerY){
            if (abs(centerX - i) > abs(centerY - j)){
                i += (centerX > i) ? 1 : -1;
            } else {
                j += (centerY > j) ? 1 : -1;
            }
            terrain[j][i] = '#';
        }
    }
    if (vPos > 0) {
        terrain[0][x2] = '#';
        i = x2; j = 1;
        terrain[j][i] = '#';
        while(i != centerX || j != centerY){
            if (abs(centerX - i) > abs(centerY - j)){
                i += (centerX > i) ? 1 : -1;
            } else {
                j += (centerY > j) ? 1 : -1;
            }
            terrain[j][i] = '#';
        }
    }
}

char Board::getTerrainAT(int r, int c) const {return terrain[r][c];}

void Board::placeBuildings()
{
    int x = rand() % 74 + 3;
    int y = rand() % 15 + 3;
    int md = abs(hPos - 200) + abs(vPos - 200);
    md = (md < 200) ? md : 200;
    if (rand() % 100 <= (-45*md/200)+50 || (hPos == 200 && vPos ==200)){
        for (int i = 0; i < 80; i++){
            if (terrain[y][i] == '#'){
                if(placeCenter(i, y)){
                    break;
                }
            }
        }
    }
    if (rand() % 100 <= (-45*md/200)+50 || (hPos == 200 && vPos ==200)){
        for (int j = 0; j < 21; j++){
            if (terrain[j][x] == '#'){
                if(placeMart(x, j)){
                    break;
                }
            }
        }
    }
    
}

bool Board::inBounds2x2(int x, int y, int dx, int dy) const
{    
    return (x  > 0 && x  < WIDTH-1  &&
            dx > 0 && dx < WIDTH-1  &&
            y  > 0 && y  < HEIGHT-1 &&
            dy > 0 && dy < HEIGHT-1);
}

bool Board::isBlocked(char tile) const
{
    // Blocks roads and existing buildings
    return (tile == '#' || tile == 'c' || tile == 'm');
}

bool Board::canPlace2x2(int x, int y, int dx, int dy) const
{
    if (!inBounds2x2(x, y, dx, dy)) {
        return false;
    }

    // check if all tiles are not blocked
    return (!isBlocked(terrain[y][x])  &&
            !isBlocked(terrain[y][dx]) &&
            !isBlocked(terrain[dy][x]) &&
            !isBlocked(terrain[dy][dx]));
}

bool Board::placeMart(int x, int y)
{
    int t = -1, bo = -1, l = -1, r = -1;

    if (canPlace2x2(x-2, y, x-1, y-1)) {
        t = y-1; bo = y;   l = x-2; r = x-1;
    } else if (canPlace2x2(x-2, y,   x-1, y+1)) {
        t = y;   bo = y+1; l = x-2; r = x-1;
    } else if (canPlace2x2(x-1, y-2, x,   y-1)) {
        t = y-2; bo = y-1; l = x-1; r = x;
    } else if (canPlace2x2(x,   y-2, x+1, y-1)) {
        t = y-2; bo = y-1; l = x;   r = x+1;
    } else if (canPlace2x2(x+1, y,   x+2, y-1)) {
        t = y-1; bo = y;   l = x+1; r = x+2;
    } else if (canPlace2x2(x+1, y,   x+2, y+1)) {
        t = y;   bo = y+1; l = x+1; r = x+2;
    } else if (canPlace2x2(x,   y+1, x+1, y+2)) {
        t = y+1; bo = y+2; l = x;   r = x+1;
    } else if (canPlace2x2(x-1, y+1, x,   y+2)) {
        t = y+1; bo = y+2; l = x-1; r = x;
    } else {
        // No valid placement found
        return false;
    }

    terrain[t][l]  = 'm';
    terrain[t][r]  = 'm';
    terrain[bo][l] = 'm';
    terrain[bo][r] = 'm';
    return true;
}

bool Board::placeCenter(int x, int y)
{
    int t = -1, bo = -1, l = -1, r = -1;

    if (canPlace2x2(x-2, y,   x-1, y-1)) {
        t = y-1; bo = y;   l = x-2; r = x-1;
    } else if (canPlace2x2(x-2, y,   x-1, y+1)) {
        t = y;   bo = y+1; l = x-2; r = x-1;
    } else if (canPlace2x2(x-1, y-2, x,   y-1)) {
        t = y-2; bo = y-1; l = x-1; r = x;
    } else if (canPlace2x2(x,   y-2, x+1, y-1)) {
        t = y-2; bo = y-1; l = x;   r = x+1;
    } else if (canPlace2x2(x+1, y,   x+2, y-1)) {
        t = y-1; bo = y;   l = x+1; r = x+2;
    } else if (canPlace2x2(x+1, y,   x+2, y+1)) {
        t = y;   bo = y+1; l = x+1; r = x+2;
    } else if (canPlace2x2(x,   y+1, x+1, y+2)) {
        t = y+1; bo = y+2; l = x;   r = x+1;
    } else if (canPlace2x2(x-1, y+1, x,   y+2)) {
        t = y+1; bo = y+2; l = x-1; r = x;
    } else {
        return false;
    }

    terrain[t][l]  = 'c';
    terrain[t][r]  = 'c';
    terrain[bo][l] = 'c';
    terrain[bo][r] = 'c';

    return true;
}