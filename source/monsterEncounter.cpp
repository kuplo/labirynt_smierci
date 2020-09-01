#include "./../headers/monsterEncounter.h"
reportableObject monsterEncounter::logger;

monster monsterEncounter::testMonster() {
    monster newMonster;
    newMonster.name = "ugly monster";
    newMonster.strength = 3;
    return newMonster;
}

bool monsterEncounter::isMonsterDrawn(tile& currentTile) {
    tileType type= currentTile.getTileType();

    //no encounter tiles
    if (type == tileType::entrance || type == tileType::none)return false;
    
    //case for already visited tile
    if (!currentTile.isaFirstEnter()) {
        unsigned diceRoll = dice6();
        if (diceRoll == 1)return true;
        return false;
    }

    //case for corridor
    if (type == tileType::corridor) {
        unsigned diceRoll = dice6();
        if (diceRoll == 1)return true;
        return false;
    }
    //case for any other tile
    unsigned diceRoll = dice6();
    if (4 > diceRoll)return true;
    return false;
}

void monsterEncounter::resolveMonsterEncounter(tile& currentTile) {
    bool encountered = false;

    if (currentTile.isOccupiedByMonsters())
    {
        logger.log(logType::INFO, "tile already occupied");
        encountered = true;
    }
    else
    {
        if (encountered = isMonsterDrawn(currentTile);encountered)
        {
        	logger.log(logType::INFO, "new monster on tile");
        	currentTile.addMonster(testMonster());
        }
    }

    encountered ? logger.log(logType::INFO, "monster has been encountered"):
    		logger.log(logType::INFO, "no monster. proceeding to next phase");

    currentTile.changeWasEnteredBeforeStatus();
    return;
}
