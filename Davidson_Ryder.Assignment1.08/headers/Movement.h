#pragma once

#include "Board.h"

enum class Type {
    Hiker,
    Rival,
    Trainer,
    Swimmer,
    Other
};


struct Cost {
    int cost;
    int weight;
    int row;
    int col;
};

class MovementCosts {
public:
    static constexpr int INF = 1000000;
    explicit MovementCosts(const Board& board);

    void updateCosts(const Board& board, int row, int col);

    const Cost& hikerAt(int row, int col) const;
    const Cost& rivalAt(int row, int col) const;
    const Cost& trainerAt(int row, int col) const;
    const Cost& swimmerAt(int row, int col) const;
    const Cost& otherAt(int row, int col) const;

    void printCosts() const;

private:

    Cost hiker[21][80];
    Cost rival[21][80];
    Cost trainer[21][80];
    Cost swimmer[21][80];
    Cost other[21][80];

    void resetCosts(const Board& board);

    void hikerCosts(int row, int col);
    void rivalCosts(int row, int col);
    void trainerCosts(int row, int col);
    void swimmerCosts(int row, int col);
    void otherCosts(int row, int col);

    static int findCost(char terrain, Type t);
    static bool checkValidPos(int row, int col);
};