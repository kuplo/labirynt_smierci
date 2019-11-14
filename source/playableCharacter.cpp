#include "./../headers/playableCharacter.h"

void playableCharacter::assignDamage(unsigned amount) {
    strength -= amount;
    log(logType::INFO, "player "+name+" suffer "+std::to_string(amount)+" damage");
    if (strength <= 0) {
        modifiers.insert(characterModifiers::death);
    }
}
bool playableCharacter::isAffectedBy(characterModifiers modifier) {
    if (modifiers.find(modifier) == modifiers.end())return false;
    return true;
}

bool playableCharacter::haveAbility(characterAbilities ability) {
    if (abilities.find(ability) == abilities.end()) return false;
    return true;
}
unsigned playableCharacter::getAbilityLevel(characterAbilities ability) {
    if (abilities.find(ability) == abilities.end())return 0;
    return abilities[ability];
}