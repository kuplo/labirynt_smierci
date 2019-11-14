#include"./../headers/board.h"


void changePosition(std::pair<int, int>& coords, relativePosition rpos) {
    switch (rpos)
    {
    case right:
        coords.first += 5;
        break;
    case up:
        coords.second += 5;
        break;
    case left:
        coords.first -= 5;
        break;
    case down:
        coords.second -= 5;
        break;
    case center:
        break;
    default:
        break;
    }
}

void board::addTile(tile& Tile, relativePosition rpos) {
    auto currentTile = tileMapping.find(currentTeamPosition)->second.get();
    std::pair<int, int> newTilePosition=currentTeamPosition;
    changePosition(newTilePosition, rpos);
    tileMapping.insert({ newTilePosition,Tile });
    log(logType::INFO, "tile with id: " + std::to_string(Tile.getId())+
        " inserted on position "+std::to_string(newTilePosition.first)+
        " "+ std::to_string(newTilePosition.second));
}



void board::addTile(const std::string& fileName) {
  
    startingTile = new tile(0,tileType::entrance);
    startingTile->loadTile(fileName, { tileBoundaryType::blocked,
        tileBoundaryType::corridor, tileBoundaryType::blocked, tileBoundaryType::blocked },tileRotation::x0);
    tileMapping.insert({ {0,0},*startingTile });
}


void board::changePositionOfParty(relativePosition pos) {
    changePosition(currentTeamPosition, pos);
}


std::array<tileBoundaryType, 4> board::getBoundariesOfNeighbourTile(relativePosition rpos) {

    std::cout << std::endl;
    std::array<tileBoundaryType, 4> boundaries;
    std::pair<int, int> newTilePosition = currentTeamPosition;
    changePosition(newTilePosition, rpos);

    auto tmp = tileMapping.find({ newTilePosition.first + 5,newTilePosition.second });
    if(tmp == tileMapping.end())boundaries[0] = tileBoundaryType::clear;
    else boundaries[0] = tmp->second.get().getBoundary(relativePosition::left);

    
    tmp = tileMapping.find({ newTilePosition.first,newTilePosition.second+5 });
    if (tmp == tileMapping.end())boundaries[1] = tileBoundaryType::clear;
    else boundaries[1] = tmp->second.get().getBoundary(relativePosition::down);

   

    tmp = tileMapping.find({ newTilePosition.first -5,newTilePosition.second });

    if (tmp == tileMapping.end())boundaries[2] = tileBoundaryType::clear;
    else boundaries[2] = tmp->second.get().getBoundary(relativePosition::right);

    tmp = tileMapping.find({ newTilePosition.first,newTilePosition.second-5 });
    if (tmp == tileMapping.end())boundaries[3] = tileBoundaryType::clear;
    else boundaries[3] = tmp->second.get().getBoundary(relativePosition::up);

    return boundaries;
}

moveActionResponse board::moveActionRequest(relativePosition rpos) {
    log(logType::INFO, "received move request");
    tile& currentTile = getCurrentTile();
    if (currentTile.getBoundary(rpos) == tileBoundaryType::blocked)return moveActionResponse::notAllowed;

    std::pair<int, int> expectedTeamPosition = currentTeamPosition;
    changePosition(expectedTeamPosition, rpos);
    auto tmp = tileMapping.find(expectedTeamPosition);
    if (tmp == tileMapping.end() )return moveActionResponse::addTile;
 
    return moveActionResponse::simpleMove;
}


tile& board::getCurrentTile() {
    tile& currentTile = tileMapping.find(currentTeamPosition)->second.get();
    return currentTile;
}
std::pair<int, int> board::getCurrentTeamPosition() {
    return currentTeamPosition;
}

board::board() {
    addTile("entrance");
    currentTeamPosition = { 0,0 };
    log(logType::INFO, "entrance added on map");
}

board::~board() {
    delete startingTile;
}

