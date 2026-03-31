#include "Movement.h"
#include "Heap.h"
#include "Comparable.h"
#include <cstdio>

struct CostNode : public Comparable<CostNode> {
    int row;
    int col;
    int cost;
    CostNode() = default;
    CostNode(int row, int col, int cost) : row(row), col(col), cost(cost) {}

    int compareTo(const CostNode other) const override {
        return cost - other.cost;
    }
};

MovementCosts::MovementCosts(const Board& board) {
    resetCosts(board);
}

bool MovementCosts::checkValidPos(int row, int col) {
    return (row > 0 && row < 20 && col > 0 && col < 79);
}

void MovementCosts::resetCosts(const Board& board) {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            Cost* grids[] = {
                &hiker[i][j], &rival[i][j], &trainer[i][j],
                &swimmer[i][j], &other[i][j]
            };

            for (Cost* c : grids) {
                c->row = i;
                c->col = j;
                c->cost = INF;
            }

            hiker[i][j].weight   = findCost(board.getTerrainAT(i,j), Type::Hiker);
            rival[i][j].weight  = findCost(board.getTerrainAT(i,j), Type::Rival);
            trainer[i][j].weight= findCost(board.getTerrainAT(i,j), Type::Trainer);
            swimmer[i][j].weight= findCost(board.getTerrainAT(i,j), Type::Swimmer);
            other[i][j].weight  = findCost(board.getTerrainAT(i,j), Type::Other);
        }
    }
}

void MovementCosts::hikerCosts(int row, int col) {
    Heap<CostNode> h;
    h.add(CostNode(row, col, 0));

    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!h.isEmpty()) {
        CostNode u = h.pop();

        if (u.cost >= hiker[u.row][u.col].cost)
            continue;

        hiker[u.row][u.col].cost = u.cost;

        for (int i = 0; i < 8; i++) {
            int nr = u.row + dr[i];
            int nc = u.col + dc[i];

            if (checkValidPos(nr, nc)) {
                int newCost = u.cost + hiker[nr][nc].weight;
                if (newCost < hiker[nr][nc].cost) {
                    h.add({nr, nc, newCost});
                }
            }
        }
    }
}

void MovementCosts::rivalCosts(int row, int col) {
    Heap<CostNode> h;
    h.add({row, col, 0});

    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!h.isEmpty()) {
        CostNode u = h.pop();

        if (u.cost >= rival[u.row][u.col].cost)
            continue;

        rival[u.row][u.col].cost = u.cost;

        for (int i = 0; i < 8; i++) {
            int nr = u.row + dr[i];
            int nc = u.col + dc[i];

            if (checkValidPos(nr, nc)) {
                int newCost = u.cost + rival[nr][nc].weight;
                if (newCost < rival[nr][nc].cost) {
                    h.add({nr, nc, newCost});
                }
            }
        }
    }
}



void MovementCosts::trainerCosts(int row, int col) {
    Heap<CostNode> h;
    h.add({row, col, 0});

    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!h.isEmpty()) {
        CostNode u = h.pop();
        if (u.cost >= trainer[u.row][u.col].cost) continue;

        trainer[u.row][u.col].cost = u.cost;

        for (int i = 0; i < 8; i++) {
            int nr = u.row + dr[i];
            int nc = u.col + dc[i];
            if (checkValidPos(nr, nc)) {
                int newCost = u.cost + trainer[nr][nc].weight;
                if (newCost < trainer[nr][nc].cost)
                    h.add({nr, nc, newCost});
            }
        }
    }
}

void MovementCosts::swimmerCosts(int row, int col) {
    Heap<CostNode> h;
    h.add({row, col, 0});

    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!h.isEmpty()) {
        CostNode u = h.pop();
        if (u.cost >= swimmer[u.row][u.col].cost) continue;

        swimmer[u.row][u.col].cost = u.cost;

        for (int i = 0; i < 8; i++) {
            int nr = u.row + dr[i];
            int nc = u.col + dc[i];
            if (checkValidPos(nr, nc)) {
                int newCost = u.cost + swimmer[nr][nc].weight;
                if (newCost < swimmer[nr][nc].cost)
                    h.add({nr, nc, newCost});
            }
        }
    }
}

void MovementCosts::otherCosts(int row, int col) {
    Heap<CostNode> h;
    h.add({row, col, 0});

    int dr[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dc[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!h.isEmpty()) {
        CostNode u = h.pop();
        if (u.cost >= other[u.row][u.col].cost) continue;

        other[u.row][u.col].cost = u.cost;

        for (int i = 0; i < 8; i++) {
            int nr = u.row + dr[i];
            int nc = u.col + dc[i];
            if (checkValidPos(nr, nc)) {
                int newCost = u.cost + other[nr][nc].weight;
                if (newCost < other[nr][nc].cost)
                    h.add({nr, nc, newCost});
            }
        }
    }
}

void MovementCosts::updateCosts(const Board& board, int row, int col) {
    resetCosts(board);
    hikerCosts(row, col);
    rivalCosts(row, col);
    trainerCosts(row, col);
    swimmerCosts(row, col);
    otherCosts(row, col);
}

int MovementCosts::findCost(char c, Type t) {
    if (t == Type::Hiker){
        switch (c){
            case '%':
                return 15;
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 15;
            case '^':
                return 15;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    }else if (t == Type::Rival){
        switch (c) {
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 20;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    } else if (t == Type::Swimmer){
        switch (c) {
            case '~':
                return 7;
            default:
                return INF;
        }
    } else if (t == Type::Other){
        switch (c) {
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 20;
            case 'm':
                return 50;
            case 'c':
                return 50;
            default:
                return INF;
        }
    } else {
        switch (c) {
            case '#':
                return 10;
            case '.':
                return 10;
            case ':':
                return 20;
            case 'm':
                return 10;
            case 'c':
                return 10;
            default:
                return INF;
        }
    }
    return INF;
}

const Cost& MovementCosts::hikerAt(int r, int c) const { return hiker[r][c]; }
const Cost& MovementCosts::rivalAt(int r, int c) const { return rival[r][c]; }
const Cost& MovementCosts::trainerAt(int r, int c) const { return trainer[r][c]; }
const Cost& MovementCosts::swimmerAt(int r, int c) const { return swimmer[r][c]; }
const Cost& MovementCosts::otherAt(int r, int c) const { return other[r][c]; }

void MovementCosts::printCosts() const {
    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 80; j++) {
            if (hiker[i][j].cost < INF)
                printf("%3d", hiker[i][j].cost % 100);
            else
                printf(" --");
        }
        printf("\n");
    }
}