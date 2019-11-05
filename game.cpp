#include <iostream>
#include <string>
#include<fstream>
#include<list>
#include <functional>
#include "headers/reportableObject.h"
#include "headers/tile.h"
#include "headers/board.h"
#include "headers/mapDrawer.h"
#include"headers/rotation.h"
std::string tileFolder = "./tiles/";
tile dummyTile(-1);

int main(void) {
    dummyTile.loadtile("empty.txt",tileRotation::x0);
    board Board;
    mapDrawer MapDrawer(Board);
    Board.addTile("corridor1.txt", relativePosition::up, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::up);
    Board.addTile("corridor2.txt", relativePosition::up, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::up);
    Board.addTile("corridor2.txt", relativePosition::right, tileRotation::x1);
    Board.changePositionOfParty(relativePosition::right);
    Board.addTile("corridor1.txt", relativePosition::down, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::down);
    Board.addTile("corridor1.txt", relativePosition::down, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::down);
    Board.addTile("corridor2.txt", relativePosition::down, tileRotation::x2);
    Board.changePositionOfParty(relativePosition::down);
    Board.addTile("corridor1.txt", relativePosition::left, tileRotation::x1);
    Board.changePositionOfParty(relativePosition::left);
    Board.addTile("corridor2.txt", relativePosition::left, tileRotation::x3);
    Board.changePositionOfParty(relativePosition::left);
    Board.addTile("corridor1.txt", relativePosition::up, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::up);
    Board.addTile("corridor1.txt", relativePosition::up, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::up);
    Board.addTile("corridor1.txt", relativePosition::up, tileRotation::x0);
    Board.changePositionOfParty(relativePosition::up);
    MapDrawer.drawMap();
    //Board.createBoard();
  
}