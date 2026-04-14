#include "Character.h"


Character::Character(char icon, CharacterType npcType, Type movementType)
    : icon(icon),
      movementType(movementType),
      npcType(npcType),
      vPos(0),
      hPos(0),
      defeated(false),
      party{},
      partySize(0)
{
}


Character::~Character() {
    for (int i = 0; i < partySize; ++i) {
        delete party[i];
        party[i] = nullptr;
    }
}

char Character::getIcon() const {
    return icon;
}
Type Character::getType() const {
    return movementType;
}
CharacterType Character::getNPCType() const {
    return npcType;
}
bool Character::isNPC() const {
    return npcType != CharacterType::TrainerLogic && movementType != Type::Trainer;
}
int Character::getVPos() const {
    return vPos;
}
int Character::getHPos() const {
    return hPos;
}
void Character::setPosition(int r, int c) {
    vPos = r;
    hPos = c;
}

bool Character::isDefeated(){
    return defeated;
}

void Character::defeat() {
    npcType = CharacterType::SentinelLogic;
    defeated = true;
}


bool Character::addMon(Mon* mon) {
    if (!mon || partySize >= MAX_MONS) {
        return false;
    }
    party[partySize++] = mon;
    return true;
}

// Access Pokémon (no ownership transfer)
Mon* Character::getMon(int index) const {
    if (index < 0 || index >= partySize) {
        throw std::out_of_range("Invalid party index");
    }
    return party[index];
}

// Remove Pokémon (ownership TRANSFERRED to caller)
Mon* Character::removeMon(int index) {
    if (index < 0 || index >= partySize) {
        throw std::out_of_range("Invalid party index");
    }

    Mon* removed = party[index];

    for (int i = index; i < partySize - 1; ++i) {
        party[i] = party[i + 1];
    }

    party[--partySize] = nullptr;
    return removed;
}

int Character::getPartySize() const {
    return partySize;
}

