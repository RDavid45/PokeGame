#pragma once

#include "Heap.h"
#include "SeedQueue.h"
#include "ArrayList.h"

// forward declarations
class Character;

enum type;
enum characterType;

class Board
{
public:
    static constexpr int HEIGHT = 21;
    static constexpr int WIDTH  = 80;
    static constexpr int INF    = 1000000;

    Board();

    void generate();
    void print() const;
    void update();

    void spawnNPCs(int count);
    void updatePlayer(int row, int col);

private:
    /* ========= TERRAIN ========= */
    char terrain[HEIGHT][WIDTH];

    /* ========= CHARACTER MAP ========= */
    Character* characters[HEIGHT][WIDTH];

    /* ========= MOVEMENT COSTS ========= */
    struct CostCell {
        int row, col;
        int cost, weight;
    };

    struct MovementCosts {
        CostCell hiker[HEIGHT][WIDTH];
        CostCell rival[HEIGHT][WIDTH];
        CostCell trainer[HEIGHT][WIDTH];
        CostCell swimmer[HEIGHT][WIDTH];
        CostCell other[HEIGHT][WIDTH];
    } costs;

    /* ========= MOVE SYSTEM ========= */
    struct Move {
        Character* c;
        int dx = 0, dy = 0;
        int when = 0;

        int compareTo(const Move& other) const {
            return when - other.when;
        }
    };

    Heap<Move> moveQueue;

    /* ========= GENERATION ========= */
    SeedQueue seeds;

    /* ========= INTERNAL METHODS ========= */
    void resetCosts();
    void updateCosts(int row, int col);

    void scheduleMove(const Move& m);
    void handleMove(Move& m);

    static int findCost(char terrain, type t);
    bool inBounds(int r, int c) const;
};