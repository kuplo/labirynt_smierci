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
    std::array<tileBoundaryType, 4> boundaries;
};



class tilePoolManager: public reportableObject {
    std::unordered_map < std::string, tilePool> entireTilePool;
    std::list<tile> tileUsedOnBoard;
public:
    tile& getNewTile(std::array<tileBoundaryType, 4> boundaries);
    tilePoolManager();
};