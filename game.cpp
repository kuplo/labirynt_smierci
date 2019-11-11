#include <iostream>
#include <string>
#include<fstream>
#include<list>
#include <functional>
#include <time.h>
#include "headers/reportableObject.h"
#include "headers/tile.h"
#include "headers/board.h"
#include "headers/mapDrawer.h"
#include"headers/auxilliary.h"
#include "headers/tilePoolManager.h"
#include "headers/terminalGUI.h"
std::string tileFolder = "./tiles/";
tile dummyTile(-1, tileType::none);

class game {
    board Board;
    mapDrawer MapDrawer;
    tilePoolManager TPM;
    terminalGUI GUI;
public:
    game():Board(),MapDrawer(Board),GUI(MapDrawer),TPM(){}
    void moveTeam(relativePosition rpos) {
        auto response = Board.moveActionRequest(rpos);

        switch (response)
        {
        case addTile:
            Board.addTile(TPM.getNewTile(Board.getBoundariesOfNeighbourTile(rpos)), rpos);
            Board.changePositionOfParty(rpos);
            break;
        case simpleMove:
            Board.changePositionOfParty(rpos);
            break;
        case notAllowed:
            std::cout << "illegal move" << std::endl;
            break;
        default:
            break;
        }

    }
    void draw() {
        GUI.draw(Board.getCurrentTeamPosition());
    }
    void inspectCurrentTile() {
        Board.getCurrentTile().resolveInspection();
    }
};


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

int main(void) {
    srand(time(NULL));

    dummyTile.loadTile("empty", { tileBoundaryType::clear,tileBoundaryType::clear,
        tileBoundaryType::clear,tileBoundaryType::clear }, tileRotation::x0);
  //  exit(0);
    game Game;
    while (true) {
        Game.draw();
        Game.moveTeam(getTeamNextMove());
        Game.inspectCurrentTile();
    }
    //terminalGUI GUI;
    //GUI.draw();
  
}