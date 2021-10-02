#include "./../headers/tilePoolManager.h"
#include "./../TerminalIO/headers/TerminalIOProxy.h"

namespace helpers
{
    bool boundariesMatch(
        std::array<tileBoundaryType, 4> const& proposedBorders,
        std::array<tileBoundaryType, 4> const& requiredBorders)
    {
        bool bBoundariesMatch = true;
        for(unsigned i=0; i<4; i++)
        {
            bool bm = proposedBorders[i] == requiredBorders[i] || requiredBorders[i] == tileBoundaryType::clear;
            bBoundariesMatch = bBoundariesMatch && bm;
        }
        return bBoundariesMatch;
    }

    void establishRotation(tile& newTile,  std::array<tileBoundaryType, 4> const& requiredBorders)
    {
        auto printTile = [&]()
        {
            for(int i=0;i<5;i++)
            {
                std::string line;
                for(int j=0;j<5;j++)
                {
                    line.push_back(newTile.shape[i][j]);
                }
                TerminalIOproxy::getRef().pushOutput(line, false);
            }
        
            TerminalIOproxy::getRef().pushOutput("rotate: R, place: E", true);   
        };
       
       bool bRotationEstablished = false;
       printTile();
       while(!bRotationEstablished)
       {
            char charInput = TerminalIOproxy::getRef().getInput();
            switch (charInput)
            {
            case 'R':
            case 'r':
                newTile.rotate(tileRotation::x1);
                printTile();
                break;
            case 'E':
            case 'e':
                if(boundariesMatch(newTile.boundaries, requiredBorders))
                {
                    bRotationEstablished = true;
                }
                else
                {
                    TerminalIOproxy::getRef().pushOutput("This tile can not be placed that way!", false);
                    printTile();
                }
                break;
            default:
                break;
            }   
       }
    }
}

tilePoolManager::tilePoolManager() {
    objectName = "tilePoolManager";
    addNewPool("c_bcbc", 10);
    addNewPool("c_cbbc", 10);
    addNewPool("c_bcpc", 10);
    addNewPool("r_pbbb", 10);
    addNewPool("f_pbbp", 10);
    log(logType::INFO, "tilePools inited");
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
        log(logType::INFO, "created new corridor type tile");
        break;
    case tileType::emptyRoom:
        tmp = dynamic_cast<tile*>(new emptyRoom(id, tT));
        log(logType::INFO, "created new emptyRoom type tile");
        break;
    case tileType::fountain:
        log(logType::INFO, "created new fountain type tile");
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

tile& tilePoolManager::getNewTile(std::array<tileBoundaryType, 4> const& boundaries) {
    static unsigned retries = 0;

    unsigned amountInPools = 0;
    for (auto&[key, value] : entireTilePool) {
        amountInPools += value.amount;
    }
    unsigned fate = rand() % amountInPools;
    tilePool* choosenTilePool;
    std::string tileName="";
    amountInPools = 0;
    for (auto&[key, value] : entireTilePool) {
        if (value.amount == 0)continue;
        amountInPools += value.amount;
        if (amountInPools >= fate) {
            choosenTilePool = &value;
            tileName = key;
            break;
        }
    }
    std::vector<tileRotation> matchingRotations;
    for (int i = 0; i < 4; i++) {
        if (checkifTileFitOnBoard(boundaries, choosenTilePool->boundaries))matchingRotations.push_back(static_cast<tileRotation>(i));
        rotateTileBoundaryTypeArray(choosenTilePool->boundaries);
    }

    if (!matchingRotations.size()) {
        if (retries == 100) {
            retries = 0;
            log(logType::WARNING, "can't get suitable tile");
            TerminalIOproxy::getRef().pushOutput("Cant get matching tile in that direction");
            throw std::runtime_error("Unable to get matching tile!");
        }
        retries++;
        return getNewTile(boundaries);
    }
    retries = 0;
    TerminalIOproxy::getRef().pushOutput("new tile is: " + tileName, false);
    tile* newTile = tileCreator(tileUsedOnBoard.size() + 1, choosenTilePool->TileType);
    newTile->loadTile(tileName, choosenTilePool->boundaries, tileRotation::x0);
    choosenTilePool->amount--;
    
    helpers::establishRotation(*newTile, boundaries);
    return *newTile;
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