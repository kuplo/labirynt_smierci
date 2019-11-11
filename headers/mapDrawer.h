#pragma once
#include <iostream>
#include "board.h"
#include "tile.h"
#include "reportableObject.h"
#include <functional>

class board;
class tile;
class terminalGUI;

extern tile dummyTile;
class mapDrawer:public reportableObject {
    friend class terminalGUI;
    int mapSizeX;
    int mapSizeY;
    int minX, minY, maxX, maxY;
    char** charMap;
    std::reference_wrapper<const board> Board;
    void deleteMap();
    void reshapeMap();
    //void fillMapSingleTile(tile& Tile, unsigned startingX, unsigned startingY);
    void fillMap();
    void fillMapWithSingleTile(tile& Tile, unsigned startingX, unsigned startingY);
public:
    mapDrawer(const board& gameBoard);
    void drawMap();
    ~mapDrawer();
};