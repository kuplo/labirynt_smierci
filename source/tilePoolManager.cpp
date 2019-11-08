#include "./../headers/tilePoolManager.h"

tilePoolManager::tilePoolManager() {
    tilePool tp;
    tp.amount = 0;
    tp.boundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::corridor };
    entireTilePool["corridor1"] = tp;
    tp.amount = 0;
    tp.boundaries = { tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::blocked,tileBoundaryType::corridor };
    entireTilePool["corridor2"] = tp;
    tp.amount = 10;
    tp.boundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor };
    entireTilePool["corridor3"] = tp;
}


bool checkifTileFitOnBoard( std::array<tileBoundaryType, 4> requestedBoundaries, std::array<tileBoundaryType, 4> tileBoundaries) {
    bool canConnect = true;
    for (int i = 0; i < 4; i++) {
        auto b1 = requestedBoundaries[i];
        auto b2 = tileBoundaries[i];
        std::cout << b1 << ' ' << b2 << std::endl;
        if (b1 == tileBoundaryType::clear) { 
            canConnect = canConnect && true; 
            continue;
        }
        if (b1 == b2) {
            canConnect = canConnect && true;
            continue;
        }
        canConnect = canConnect && false;
        
    }
    std::cout << std::endl;
    return canConnect;
}

tile& tilePoolManager::getNewTile(std::array<tileBoundaryType, 4> boundaries) {
    unsigned amountInPools = 0;
    for (auto&[key, value] : entireTilePool) {
        amountInPools += value.amount;
    }
    unsigned fate = rand() % amountInPools;
    tilePool choosenTilePool;
    std::string tileName="";
    amountInPools = 0;
    for (auto&[key, value] : entireTilePool) {
        if (value.amount == 0)continue;
        amountInPools += value.amount;
        if (amountInPools >= fate) {
            choosenTilePool = value;
            tileName = key;
            break;
        }
    }
    std::vector<tileRotation> matchingRotations;
    for (int i = 0; i < 4; i++) {
        if (checkifTileFitOnBoard(boundaries, choosenTilePool.boundaries))matchingRotations.push_back(static_cast<tileRotation>(i));
        rotateTileBoundaryTypeArray(choosenTilePool.boundaries);
    }
  //  exit(0);
    if (!matchingRotations.size()) return getNewTile(boundaries);
    
    std::cout << "rotation available: ";
    for (int i = 0; i < matchingRotations.size(); i++) {
        std::cout << matchingRotations[i] << ' ';
    }
    std::cout << " choose" << std::endl;
    unsigned choice;
    std::cin >> choice;
    tile Tile(tileUsedOnBoard.size()+1);
    tileUsedOnBoard.push_back(Tile);
    tileUsedOnBoard.rbegin()->loadTile(tileName, choosenTilePool.boundaries, static_cast<tileRotation>(choice));
    choosenTilePool.amount--;
    return *tileUsedOnBoard.rbegin();
}