#include "Character.h"


Character::Character(char icon, CharacterType npcType, Type movementType) : icon(icon), movementType(movementType), npcType(npcType), vPos(0), hPos(0) {}

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
void Character::defeat() {
    npcType = CharacterType::SentinelLogic;
}
