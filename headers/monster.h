#pragma once
#include "auxilliary.h"
#include "reportableObject.h"

enum class specialAbilities{none,fireBreath,stench,stoneTransform,regeneration,charm};
class monster : public reportableObject {
public:
    std::string name;
    unsigned strength;
    unsigned agility;
    unsigned NNcoeff;
    weaponType weapon;
    specialAbilities specialAbility;
    //spells
    monster(const monster& Monster);
    monster();
};