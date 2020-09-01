#pragma once
#include "auxilliary.h"
#include "reportableObject.h"
#include "monster.h"
#include "tile.h"

class monsterEncounter:public reportableObject {
    static monster testMonster();
    static reportableObject logger;
    static bool isMonsterDrawn(tile& currentTile);
public:
    static void resolveMonsterEncounter(tile& currentTile);
};