#include"./../headers/board.h"

unsigned board::numberOfTiles = 0;

void board::linkTwoTiles(int id1, relativePosition position1, int id2, relativePosition position2) {
    tileAndNeigbours* t1 = NULL;
    tileAndNeigbours* t2 = NULL;
    for (auto& ptr : listOfTilesAndNeighbours) {
        if (id1 == ptr.first->getId())t1 = &ptr;
        if (id2 == ptr.first->getId())t2 = &ptr;
    }
    if (t1 == NULL || t2 == NULL) {
        log(logType::ERROR, "error in pairing tiles: " + std::to_string(id1) + " and " + std::to_string(id1));
        return;
    }
    t1->second[position1] = *(t2->first);
    t1->second[position2] = *(t1->first);
}

void board::addTile(const std::string& fileName, relativePosition rpos,tileRotation rot) {
    std::vector<std::reference_wrapper<tile>> listOfNeighbours;
    for (int i = 0; i < 4; i++)listOfNeighbours.push_back(dummyTile);
    tile* Tile = new tile(numberOfTiles++);
    Tile->loadtile(fileName, rot);
    listOfTilesAndNeighbours.push_back(std::pair(Tile, listOfNeighbours));

    auto currentTile = tileMapping.find(currentTeamPosition)->second.get();
    linkTwoTiles(currentTile.getId(),
        rpos, Tile->getId(), static_cast<relativePosition>((static_cast<unsigned>(rpos) +2)%4) );

    std::pair<int, int> newTilePosition=currentTeamPosition;
    switch (rpos)
    {
    case right:
        newTilePosition.second = newTilePosition.second + 5;
        break;
    case up:
        newTilePosition.first = newTilePosition.first + 5;
        break;
    case left:
        newTilePosition.second = newTilePosition.second - 5;
        break;
    case down:
        newTilePosition.first = newTilePosition.first - 5;
        break;
    default:
        break;
    }
    tileMapping.insert({ newTilePosition,*Tile });
}
void board::addTile(const std::string& fileName) {
    std::vector<std::reference_wrapper<tile>> listOfNeighbours;
    for (int i = 0; i < 4; i++)listOfNeighbours.push_back(dummyTile);
    tile* Tile = new tile(numberOfTiles++);
    Tile->loadtile(fileName, tileRotation::x0);
    listOfTilesAndNeighbours.push_back(std::make_pair(Tile, listOfNeighbours));
    tileMapping.insert({ {0,0},*Tile });
}


void board::changePositionOfParty(relativePosition pos) {
    switch (pos)
    {
    case right:
        currentTeamPosition.second += 5;
        break;
    case up:
        currentTeamPosition.first += 5;
        break;
    case left:
        currentTeamPosition.second -= 5;
        break;
    case down:
        currentTeamPosition.first -= 5;
        break;
    default:
        break;
    }
}

board::board() {
    addTile("entrance.txt");
    currentTeamPosition = { 0,0 };
}

board::~board() {
    for (auto& ptr : listOfTilesAndNeighbours) {
        delete ptr.first;
    }
}

