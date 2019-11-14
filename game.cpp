#include <iostream>
#include <string>
#include<fstream>
#include<list>
#include <functional>
#include <time.h>
#include <queue>
#include "headers/reportableObject.h"
#include "headers/tile.h"
#include "headers/board.h"
#include "headers/mapDrawer.h"
#include"headers/auxilliary.h"
#include "headers/tilePoolManager.h"
#include "headers/terminalGUI.h"
#include "headers/playableCharacter.h"
#include "headers/trapResolver.h"

enum class turnPhase {init,move,passageTrap,monsterEncounter,tileInspection,exit};
std::string tileFolder = "./tiles/";
tile dummyTile(-1, tileType::none);
bool run_game = true;


relativePosition getTeamNextMove() {
    char i = ' ';
    //  std::cout << "RUCH" << std::endl;
    std::cin >> i;
    switch (i) {
    case 'd':
        return relativePosition::right;
        break;
    case 'w':
        return relativePosition::up;
        break;
    case 'a':
        return relativePosition::left;
        break;
    case 's':
        return relativePosition::down;
        break;
    default:
        return relativePosition::up;
        break;
    }
}

class game : public reportableObject{

    std::queue<turnPhase> phaseOrder;
    board Board;
    mapDrawer MapDrawer;
    tilePoolManager TPM;
    terminalGUI GUI;
    std::vector<playableCharacter> team;
    playableCharacter* currentTeamLeader;
    void temporaryCharacter() {
        playableCharacter temp;
        temp.type = characterType::adept;
        temp.name = "test character";
        temp.experience = 0;
        temp.gold = 0;
        temp.jewelry = 0;
        temp.magicalPotential = { 2,2,2 };
        temp.proficiency[weaponType::bow] = 1;
        temp.resistance = 2;
        temp.strength = 2;
        temp.weapons.push_back(weaponType::bow);
        temp.abilities[characterAbilities::trapDismantle] = 1;
        team.push_back(temp);
    }
public:
    game():Board(),MapDrawer(Board),GUI(MapDrawer),TPM(){ 
        temporaryCharacter();
        currentTeamLeader = &(*team.begin());
        phaseOrder.push(turnPhase::init);
    }
    void moveTeam(relativePosition rpos) {
        auto response = Board.moveActionRequest(rpos);

        switch (response)
        {
        case addTile:
            log(logType::INFO, "received add tile response");
            Board.addTile(TPM.getNewTile(Board.getBoundariesOfNeighbourTile(rpos)), rpos);
            if (Board.getCurrentTile().getBoundary(rpos) == tileBoundaryType::passage)phaseOrder.push(turnPhase::passageTrap);
            Board.changePositionOfParty(rpos);
            phaseOrder.push(turnPhase::monsterEncounter);
            break;
        case simpleMove:
            log(logType::INFO, "received simple move response");
            Board.changePositionOfParty(rpos);
            if (std::pair<int, int> initPos = { 0,0 }; Board.getCurrentTeamPosition() == initPos)phaseOrder.push(turnPhase::exit);
            phaseOrder.push(turnPhase::monsterEncounter);
            break;
        case notAllowed:
            log(logType::INFO, "received not allowed response");
            std::cout << "illegal move" << std::endl;
            phaseOrder.push(turnPhase::move);
            break;
        default:
            break;
        }
 
    }
    void draw() {
        GUI.draw(Board.getCurrentTeamPosition());
    }
    void resolveTileInspection() {
        Board.getCurrentTile().resolveInspection();
    }

    void resolveMonsterEncounter() {
       // std::cout << "BOOOOOO" << std::endl;
    }
    void resolveNextPhase() {
        turnPhase nextPhase = phaseOrder.front();
        phaseOrder.pop();
        switch (nextPhase)
        {
        case turnPhase::init:
            log(logType::INFO, "Game Is Starting");
            phaseOrder.push(turnPhase::move);
            draw();
            break;
        case turnPhase::move:
            log(logType::INFO, "Moving Phase");
            std::cout << "MOVE" << std::endl;
            moveTeam(getTeamNextMove());
            draw();
            break;
        case turnPhase::passageTrap:
            log(logType::INFO, "Passage trap phase");
            trapResolver::resolvePassageTrap(*currentTeamLeader, team);
            break;
        case turnPhase::monsterEncounter:
            log(logType::INFO, "Monster encounter phase");
            resolveMonsterEncounter();
            break;
        case turnPhase::tileInspection:
            log(logType::INFO, "Tile inspection phase");
            resolveTileInspection();
            break;
        case turnPhase::exit:
            log(logType::INFO, "Party reached entrance. Exiting ...");
            run_game = false;
            return;
            break;
        default:
            break;
        }
        if (phaseOrder.size() == 0)phaseOrder.push(turnPhase::move);
    }
};




int main(void) {
    srand(time(NULL));
    dummyTile.loadTile("empty", { tileBoundaryType::clear,tileBoundaryType::clear,
        tileBoundaryType::clear,tileBoundaryType::clear }, tileRotation::x0);
  //  exit(0);
    game Game;
    while (run_game) {
        Game.resolveNextPhase();
    }

  
}