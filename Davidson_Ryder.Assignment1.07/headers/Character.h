#ifndef CHARACTER_H
#define CHARACTER_H

#include "Movement.h"
#include "Mon.h"
#include <array>
#include <stdexcept>

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
    bool defeated;

    static constexpr int MAX_MONS = 6;
    std::array<Mon*, MAX_MONS> party{};
    int partySize = 0;

public:
    Character(char icon, CharacterType npcType, Type movementType);
    ~Character();

    // Existing methods
    char getIcon() const;
    Type getType() const;
    CharacterType getNPCType() const;
    bool isNPC() const;
    int getVPos() const;
    int getHPos() const;
    void setPosition(int r, int c);
    bool isDefeated();
    void defeat();

    // Pokémon
    bool addMon(Mon* mon);
    Mon* getMon(int index) const;
    Mon* removeMon(int index);
    int getPartySize() const;
};

#endif // CHARACTER_H