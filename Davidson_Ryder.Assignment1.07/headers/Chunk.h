#include "CharacterMap.h"
#include "Board.h"
#include "Movement.h"
#include "MoveController.h"

class Chunk{
    private:
        Board board;
        MovementCosts costMap;
        CharacterMap characterMap;

        MoveController* controller;

        Move playerMove;

        int hPos, vPos;
        bool hasSpawned;

        void processUntilTime(int barrierTime);
        static char iconFor(CharacterType t);
        static CharacterType randomBehavior();
        static Type costCategoryFor(CharacterType t);

        bool isOccupied(int r, int c) const;
        bool canSpawn(Type npc, int r, int c) const;

        int generateNPCs(int num);

        int genNPCsIfNeeded();

        void printTrainerInfo(const Character& pc, const Character& npc)const;
    public:
    Chunk(int vPos, int hPos, int n, int s, int w, int e);
    ~Chunk();

    int getNGate() {return board.getNGate();}
    int getEGate() {return board.getEGate();}
    int getSGate() {return board.getSGate();}
    int getWGate() {return board.getWGate();}

    int getIntersectionRow() {return board.getCenterY();}
    int getIntersectionCol() {return board.getCenterX();}

    Move& placePlayer(Character *pc, int r, int c);
    void removePlayer();

    bool movePlayer(Move &m);


    void displayChunk()const;
    void handleShowTrainers(const Character& pc)const;
    void handleCenter(const Character& pc)const;
};