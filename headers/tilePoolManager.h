#pragma once
#include "reportableObject.h"
#include "tile.h"
#include "board.h"
#include"auxilliary.h"
#include <unordered_map>
#include <random>
#include <array>
struct tilePool {
    unsigned amount;
    tileType TileType;
    std::array<tileBoundaryType, 4> boundaries;
};



class tilePoolManager: public reportableObject {
    std::unordered_map < std::string, tilePool> entireTilePool;
    std::list<tile*> tileUsedOnBoard;
    void addNewPool(std::string tName, unsigned number);
    tile* tileCreator(int id, tileType tT);
public:
    tile& getNewTile(std::array<tileBoundaryType, 4> boundaries);
    tilePoolManager();
    ~tilePoolManager();
};