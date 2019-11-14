#include "./../headers/trapResolver.h"


reportableObject trapResolver::logger;

void trapResolver::arrow(playableCharacter& pl) {
    logger.log(logType::INFO, "resolving arrow trap");
    //TODO
}

void trapResolver::poisonArrow(playableCharacter& pl) {
    logger.log(logType::INFO, "resolving poison arrow trap");
    //TODO
}
void trapResolver::gase(playableCharacter& pl) {
    logger.log(logType::INFO, "resolving gase trap");
    unsigned diceResult = dice3();
    pl.assignDamage(diceResult);
}
void trapResolver::explosion(std::vector<playableCharacter>& team) {
    logger.log(logType::INFO, "resolving explosion trap");
    for (auto& pl : team) {
        pl.assignDamage(1);
    }
}

void trapResolver::oil(playableCharacter& pl) {
    logger.log(logType::INFO, "resolving oil trap");
    unsigned diceResult = dice3();
    pl.assignDamage(diceResult);
}


bool trapResolver::tryToDismantleTrap(playableCharacter& pl) {
    unsigned diceResult = dice6();
    if (diceResult > pl.getAbilityLevel(characterAbilities::trapDismantle)) {
        logger.log(logType::INFO, "trap was not dismantled");
        return false; 
    }
    logger.log(logType::INFO, "trap was dismantled");
    return true;
}

void trapResolver::resolvePassageTrap(playableCharacter& currentPlayer, std::vector<playableCharacter>& team) {
    unsigned diceResult = dice6();
    if (diceResult == 1) {
        std::cout << "it's a trap!" << std::endl;
        std::vector<std::reference_wrapper<playableCharacter>> validCharacters;
        for (auto& pl : team) {
            if (pl.haveAbility(characterAbilities::trapDismantle))validCharacters.push_back(pl);
        }
        if (validCharacters.size() == 0)resolveTrap(currentPlayer, team);
        else {
            validCharacters.push_back(currentPlayer);
            std::cout << "choose player (0-5): ";
            for (auto& pl : validCharacters)
                std::cout << pl.get().name << ' ';
            std::cout << std::endl;
            unsigned choice;
            std::cin >> choice;
            if(! tryToDismantleTrap(validCharacters[choice].get()))resolveTrap(validCharacters[choice].get(), team);
        }
    }
}

void trapResolver::resolveTrap(playableCharacter& pl, std::vector<playableCharacter>& team) {
    unsigned diceResult = dice6();
    switch (diceResult)
    {
    case(1):
        arrow(pl);
        break;
    case(2):
        poisonArrow(pl);
        break;
    case(3):
        gase(pl);
        break;
    case(4):
        explosion(team);
        break;
    case(5):
        oil(pl);
        break;
    case(6):
        resolveTrap(pl,team);
        resolveTrap(pl,team);
        break;
    default:
        break;
    }
}
