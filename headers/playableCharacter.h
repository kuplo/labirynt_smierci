#pragma once
#include "reportableObject.h"
#include "auxilliary.h"
#include <unordered_map>
#include <set>
#include <list>
enum class characterType{hero,adept};
enum class characterRace{elf,dwarf,human};
enum class characterAbilities {charisma,trapDismantle,darkGate};
enum class characterModifiers{death};
class playableCharacter : public reportableObject {
public:
    characterType type;
    std::string name;
    characterRace race;
    int strength;
    std::tuple<int,int,int> magicalPotential;
    int resistance;
    int agility;
    std::unordered_map<weaponType, int> proficiency;
    std::unordered_map<characterAbilities, int> abilities;
    std::list<weaponType> weapons;
    std::set<characterModifiers> modifiers;
    //spells
    //magicalItems
    int gold;
    int jewelry;
    int experience;



    void assignDamage(unsigned amount);
    bool isAffectedBy(characterModifiers modifier);

    bool haveAbility(characterAbilities ability);
    unsigned getAbilityLevel(characterAbilities ability);
};