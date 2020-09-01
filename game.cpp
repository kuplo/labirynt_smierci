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
#include"headers/auxilliary.h"
#include "headers/tilePoolManager.h"
#include "headers/playableCharacter.h"
#include "headers/trapResolver.h"
#include "headers/monsterEncounter.h"

#include "TerminalIO/headers/TerminalGUI.h"

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
    tilePoolManager TPM;
    TerminalGUI m_TerminalGUI;
    std::vector<playableCharacter> team;
    playableCharacter* currentTeamLeader;
    std::vector < std::vector<std::reference_wrapper<playableCharacter> > >marchOrder;
    dominantSuns dominantSun;
    void temporaryCharacter(std::string name) {
        playableCharacter temp;
        temp.type = characterType::adept;
        temp.name = name;
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
    void setMarchingOrder() {
        marchOrder.push_back(std::vector<std::reference_wrapper<playableCharacter> >());
        marchOrder.push_back(std::vector<std::reference_wrapper<playableCharacter> >());
        marchOrder[0].push_back(team[1]);
        marchOrder[0].push_back(team[2]);
        marchOrder[1].push_back(team[0]);
    }
    void setDominantSun() {
        unsigned result = dice3();
        if (result == 1)dominantSun = dominantSuns::redSun;
        if (result == 1)dominantSun = dominantSuns::yellowSun;
        if (result == 1)dominantSun = dominantSuns::blueSun;
    }

public:
    game():Board(), m_TerminalGUI(),TPM(){
    	std::unique_ptr<MapDrawer> pMapDrawer = std::make_unique<MapDrawer>(Board);
    	m_TerminalGUI.setDrawer(std::move(pMapDrawer));

        temporaryCharacter("test1");
        temporaryCharacter("test2");
        temporaryCharacter("test3");
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
    	m_TerminalGUI.refreshScreen();
    }
    void resolveTileInspection() {
        Board.getCurrentTile().resolveInspection();
    }

   
    void resolveNextPhase() {
        turnPhase nextPhase = phaseOrder.front();
        phaseOrder.pop();
        switch (nextPhase)
        {
        case turnPhase::init:
            setMarchingOrder();
            setDominantSun();
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
            monsterEncounter::resolveMonsterEncounter(Board.getCurrentTile());
            if (Board.getCurrentTile().isOccupiedByMonsters()) {
                draw();
                phaseOrder.push(turnPhase::battle);
            }
            break;
        case turnPhase::battle:
            log(logType::INFO, "Battle phase");

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
