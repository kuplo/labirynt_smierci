#include "./../headers/monster.h"


monster::monster(){}
monster::monster(const monster& Monster) {
    name = Monster.name;
    strength = Monster.strength;
    agility = Monster.agility;
    NNcoeff = Monster.NNcoeff;
    weapon = Monster.weapon;
    specialAbility = Monster.specialAbility;
}