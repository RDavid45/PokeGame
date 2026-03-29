#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movement.h"

enum class CharacterType {
    TrainerLogic  = 0x00,
    HikerLogic    = 0x01,
    RivalLogic    = 0x02,
    WandererLogic = 0x04,
    SentinelLogic = 0x08,
    ExplorerLogic = 0x10,
    PacerLogic    = 0x20
};

class Character {
private:
    char icon;
    type movementType;
    CharacterType npcType;
    int vPos;
    int hPos;

public:
    Character(char icon, CharacterType npcType, type movementType);
    ~Character() = default;

    char getIcon() const;
    type getType() const;
    CharacterType getNPCType() const;
    bool isNPC() const;
    int getVPos() const;
    int getHPos() const;
    void setPosition(int vPos, int hPos);
};

#endif // CHARACTER_H