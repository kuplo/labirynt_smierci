#include "./../headers/mapDrawer.h"





   
void mapDrawer::deleteMap() {
    for (int i = 0; i < mapSizeX; i++) {
        delete charMap[i];
    }
    delete charMap;
}

void mapDrawer::reshapeMap() {
    charMap = new char*[mapSizeX];
    for (int i = 0; i < mapSizeX; i++) {
        charMap[i] = new char[mapSizeY];
    }
}


void mapDrawer::fillMapWithSingleTile(tile& Tile, unsigned startingX, unsigned startingY) {
    std::cout << startingX << ' ' << startingY << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            charMap[startingX + i][startingY + j] = Tile.shape[i][j];
           std::cout << charMap[startingX + i][startingY + j];
        }
        std::cout <<  std::endl;
    }
    std::cout << std::endl;
}

void mapDrawer::fillMap() {
    std::cout << std::endl;
    auto& tileMapping = Board.get().tileMapping;
    for (int i = minX; i <= maxX; i = i + 5) {
        for (int j = minY; j <= maxY; j = j + 5) {
            auto tileToDraw = tileMapping.find({ i,j });
            std::cout << i << ' ' << j << " type ";
            if (tileToDraw == tileMapping.end()) {
                std::cout << "1 at point ";
                fillMapWithSingleTile(dummyTile, i  + abs(minX), j  + abs(minY));
            }
            else {
               std::cout << "2 at point ";
                fillMapWithSingleTile(tileToDraw->second.get(), i + abs(minX), j +abs(minY) );
            }
        }
    }
    charMap[Board.get().currentTeamPosition.first + 1 + abs(minX)][ Board.get().currentTeamPosition.second + 1 + abs(minY)]='T';
}


mapDrawer::mapDrawer(const board& gameBoard) : Board(gameBoard) {
    minX = minY = maxX = maxY = mapSizeX = mapSizeY = 0;
    charMap = new char*[1];
}
void mapDrawer::drawMap() {
    deleteMap();
    auto& tileMapping = Board.get().tileMapping;
    minX = minY = maxX = maxY = 0;
    std::cout << "DRAWING" << std::endl;
    for (auto&[key, val] : tileMapping) {
       std::cout << key.first << ' ' << key.second << std::endl;
        if (key.first > maxX)maxX = key.first;
        if (key.first < minX)minX = key.first;
        if (key.second > maxY)maxY = key.second;
        if (key.second < minY)minY = key.second;
    }
    std::cout << std::endl;
    minX = minX - 5;
    maxX = maxX + 5;
    minY = minY - 5;
    maxY = maxY + 5;
    if (mapSizeX != maxX - minX+5)mapSizeX = maxX - minX+5;
    if (mapSizeY != maxY - minY+5)mapSizeY = maxY - minY+5;
    reshapeMap();
   std::cout << minX << ' ' << minY << " _ " << maxX << ' ' << maxY << std::endl;
   std::cout << mapSizeX << ' ' << mapSizeY << std::endl;
    fillMap();
    for (int j = 0; j < mapSizeY; j++) {
        for (int i = 0; i < mapSizeX; i++) {
       
            std::cout << charMap[i][mapSizeY-j-1] << ' ';
        }
        std::cout <<  std::endl;
    }
}

mapDrawer::~mapDrawer() {
    deleteMap();
}
