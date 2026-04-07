#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movement.h"

enum class CharacterType {
    TrainerLogic,
    HikerLogic,
    RivalLogic,
    WandererLogic,
    SentinelLogic,
    ExplorerLogic,
    PacerLogic
};

class Character {
private:
    char icon;
    Type movementType;
    CharacterType npcType;
    int vPos;
    int hPos;

public:
    Character(char icon, CharacterType npcType, Type movementType);
    ~Character() = default;

    char getIcon() const;
    Type getType() const;
    CharacterType getNPCType() const;
    bool isNPC() const;
    int getVPos() const;
    int getHPos() const;
    void setPosition(int r, int c);
    void defeat();
};

#endif // CHARACTER_H
