#include"./../headers/board.h"

//void board::linkTwoTiles(int id1, relativePosition position1, int id2, relativePosition position2) {
//    tileAndNeigbours* t1 = NULL;
//    tileAndNeigbours* t2 = NULL;
//    for (auto& ptr : listOfTilesAndNeighbours) {
//        if (id1 == ptr.first.get().getId())t1 = &ptr;
//        if (id2 == ptr.first.get().getId())t2 = &ptr;
//    }
//    if (t1 == NULL || t2 == NULL) {
//        log(logType::ERROR, "error in pairing tiles: " + std::to_string(id1) + " and " + std::to_string(id1));
//        return;
//    }
//    t1->second[position1] = (t2->first).get();
//    t1->second[position2] = (t1->first).get();
//}

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
//    std::vector<std::reference_wrapper<tile>> listOfNeighbours;
 //   for (int i = 0; i < 4; i++)listOfNeighbours.push_back(dummyTile);
 //   listOfTilesAndNeighbours.push_back({ Tile, listOfNeighbours } );
    auto currentTile = tileMapping.find(currentTeamPosition)->second.get();
    std::pair<int, int> newTilePosition=currentTeamPosition;
    changePosition(newTilePosition, rpos);
    tileMapping.insert({ newTilePosition,Tile });
}



void board::addTile(const std::string& fileName) {
  //  std::vector<std::reference_wrapper<tile>> listOfNeighbours;
  //  for (int i = 0; i < 4; i++)listOfNeighbours.push_back(dummyTile);
    startingTile = new tile(0,tileType::entrance);
    startingTile->loadTile(fileName, { tileBoundaryType::blocked,
        tileBoundaryType::corridor, tileBoundaryType::blocked, tileBoundaryType::blocked },tileRotation::x0);
  //  listOfTilesAndNeighbours.push_back({ *startingTile, listOfNeighbours });
    tileMapping.insert({ {0,0},*startingTile });
}


void board::changePositionOfParty(relativePosition pos) {
    changePosition(currentTeamPosition, pos);
}


std::array<tileBoundaryType, 4> board::getBoundariesOfNeighbourTile(relativePosition rpos) {
 /*   for (auto&[key, value] : tileMapping) {
        std::cout << key.first << ' ' << key.second << std::endl;
    }*/
    std::cout << std::endl;
    std::array<tileBoundaryType, 4> boundaries;
    std::pair<int, int> newTilePosition = currentTeamPosition;
    changePosition(newTilePosition, rpos);

  //  std::cout << "dupa" << std::endl;
    auto tmp = tileMapping.find({ newTilePosition.first + 5,newTilePosition.second });
    if(tmp == tileMapping.end())boundaries[0] = tileBoundaryType::clear;
    else boundaries[0] = tmp->second.get().getBoundary(relativePosition::left);

    
    tmp = tileMapping.find({ newTilePosition.first,newTilePosition.second+5 });
    if (tmp == tileMapping.end())boundaries[1] = tileBoundaryType::clear;
    else boundaries[1] = tmp->second.get().getBoundary(relativePosition::down);

   

    tmp = tileMapping.find({ newTilePosition.first -5,newTilePosition.second });
   // std::cout << tmp->first.first << ' ' << tmp->first.first << tmp->second.get().getId() << std::endl;
    if (tmp == tileMapping.end())boundaries[2] = tileBoundaryType::clear;
    else boundaries[2] = tmp->second.get().getBoundary(relativePosition::right);

    tmp = tileMapping.find({ newTilePosition.first,newTilePosition.second-5 });
    if (tmp == tileMapping.end())boundaries[3] = tileBoundaryType::clear;
    else boundaries[3] = tmp->second.get().getBoundary(relativePosition::up);

  //  std::cout << boundaries[0] << ' ' << boundaries[1] << ' ' << boundaries[2] << ' ' << boundaries[3] << std::endl;
    return boundaries;
}

moveActionResponse board::moveActionRequest(relativePosition rpos) {
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
}

board::~board() {
    delete startingTile;
}

