#include "./../headers/tilePoolManager.h"




tilePoolManager::tilePoolManager() {
    addNewPool("c_bcbc", 10);
    addNewPool("c_cbbc", 10);
    addNewPool("c_bcpc", 10);
    addNewPool("r_pbbb", 10);
    addNewPool("f_pbbp", 10);
}


bool checkifTileFitOnBoard( std::array<tileBoundaryType, 4> requestedBoundaries, std::array<tileBoundaryType, 4> tileBoundaries) {
    bool canConnect = true;
    for (int i = 0; i < 4; i++) {
        auto b1 = requestedBoundaries[i];
        auto b2 = tileBoundaries[i];
    //    std::cout << b1 << ' ' << b2 << std::endl;
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
 //   std::cout << std::endl;
    return canConnect;
}
tile* tilePoolManager::tileCreator(int id, tileType tT) {
    tile* tmp;
    switch (tT)
    {
    case tileType::none:
        break;
    case tileType::entrance:
        break;
    case tileType::corridor:
        tmp =dynamic_cast<tile*>( new corridor(id, tT) );
        break;
    case tileType::emptyRoom:
        tmp = dynamic_cast<tile*>(new emptyRoom(id, tT));
        break;
    case tileType::fountain:
        tmp = dynamic_cast<tile*>(new fountain(id, tT));
        break;
    case tileType::figure:
        break;
    case tileType::trapDoor:
        break;
    case tileType::mirror:
        break;
    case tileType::furniture:
        break;
    case tileType::altar:
        break;
    case tileType::art:
        break;
    case tileType::stairs:
        break;
    default:
        break;
    }
    tileUsedOnBoard.push_back(tmp);
    return tmp;
}

tile& tilePoolManager::getNewTile(std::array<tileBoundaryType, 4> boundaries) {
    static unsigned retries = 0;

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
    if (!matchingRotations.size()) {
        if (retries == 100) {
            retries = 0;
            std::cout << "Cant get matching tile in that direction" << std::endl;
            exit(0);
        }
        retries++;
        return getNewTile(boundaries);
    }
    retries = 0;
    std::cout << "new tile is: " << tileName << std::endl;
    std::cout << "rotation available: ";
    for (int i = 0; i < matchingRotations.size(); i++) {
        std::cout << matchingRotations[i] << ' ';
    }
    std::cout << " choose" << std::endl;
    unsigned choice;
    std::cin >> choice;
 

    tile* Tile = tileCreator(tileUsedOnBoard.size() + 1, choosenTilePool.TileType);
    Tile->loadTile(tileName, choosenTilePool.boundaries, static_cast<tileRotation>(choice));
    choosenTilePool.amount--;
  //  std::cout << "dupa" << std::endl;
    return *Tile;
}

tileType deduceTileType(char ch) {
    switch (ch)
    {
    case 'c':
        return tileType::corridor;
    case 'r':
        return tileType::emptyRoom;
    case 'f':
        return tileType::fountain;
    default:
        return tileType::none;
    }
}
tileBoundaryType deduceBoundary(char ch) {
    switch (ch)
    {
    case 'b':
        return  tileBoundaryType::blocked;
    case 'c':
        return tileBoundaryType::corridor;
    case 'p':
        return tileBoundaryType::passage;
    default:
        return tileBoundaryType::clear;
    }
}

void tilePoolManager::addNewPool(std::string tileName, unsigned amount) {
    tilePool tp;
    tp.amount = amount;
    tp.TileType = deduceTileType(tileName[0]);
    for (int i = 0; i < 4; i++) {
        tp.boundaries[i] = deduceBoundary(tileName[i+2]);
    }
    entireTilePool[tileName] = tp;
}

tilePoolManager::~tilePoolManager() {
    for (auto& it : tileUsedOnBoard) {
        delete it;
    }
}