#pragma once
#include "playableCharacter.h"
#include "reportableObject.h"
#include "auxilliary.h"
#include <list>
#include <vector>
#include <functional>
//enum class trapType {arrow,poisonArrow,gase,explosion,oil};

struct trapResolver: public reportableObject {
    static reportableObject logger;
    trapResolver() = delete;
    void static resolvePassageTrap(playableCharacter& currentPlayer, std::vector<playableCharacter>& team);
    bool static tryToDismantleTrap(playableCharacter& pl);

    void static arrow(playableCharacter& pl);
    void static poisonArrow(playableCharacter& pl);
    void static gase(playableCharacter& pl);
    void static explosion(std::vector<playableCharacter>& team);
    void static oil(playableCharacter& pl);

    void static resolveTrap(playableCharacter& pl, std::vector<playableCharacter>& team);
};
