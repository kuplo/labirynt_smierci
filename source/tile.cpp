#include "./../headers/tile.h"

tile::tile(int id, tileType tT) :id(id), TileType(tT) { objectName = "tile" + std::to_string(id); }

int&& tile::getId() { return std::move(id); }
tileType tile::getTileType() { return TileType; }
void tile::rotate90degrees() {
    int N = 5;
    for (int x = 0; x < N / 2; x++)
        for (int y = x; y < N - x - 1; y++)
        {
            char temp = shape[x][y];
            shape[x][y] = shape[y][N - 1 - x];
            shape[y][N - 1 - x] = shape[N - 1 - x][N - 1 - y];
            shape[N - 1 - x][N - 1 - y] = shape[N - 1 - y][x];
            shape[N - 1 - y][x] = temp;
        }
   




  /*  for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            char temp = shape[i][j];
            shape[i][j] = shape[N - 1 - j][i];
            shape[N - 1 - j][i] = shape[N - 1 - i][N - 1 - j];
            shape[N - 1 - i][N - 1 - j] = shape[j][N - 1 - i];
            shape[j][N - 1 - i] = temp;
        }
    }*/
}
void tile::rotate(tileRotation rot) {
  /*  char temporary[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            temporary[i][j] = shape[i][j];*/
    switch(rot) {
        case x0:
            break;
        case x1:
            rotate90degrees();
            rotateTileBoundaryTypeArray(boundaries);
            break;
        case x2:
            rotate90degrees();
            rotate90degrees();
            rotateTileBoundaryTypeArray(boundaries);
            rotateTileBoundaryTypeArray(boundaries);
            break;
        case x3:
            rotate90degrees();
            rotate90degrees();
            rotate90degrees();
            rotateTileBoundaryTypeArray(boundaries);
            rotateTileBoundaryTypeArray(boundaries);
            rotateTileBoundaryTypeArray(boundaries);
        default:
            break;
    }
}

void tile::loadTile(const std::string& fileName,std::array<tileBoundaryType,4> preRotationBoundaries, tileRotation rot) {
    std::ifstream tileFile(tileFolder + fileName+".txt");
    std::string line;
    if (tileFile.is_open()) {
        unsigned i = 0;
        while (std::getline(tileFile, line))
        {
            unsigned j = 0;
            for (int j = 0; j < 5; j++) {
                shape[j][4-i] = line[j];
            }
            i++;
        }
        tileFile.close();
        boundaries = preRotationBoundaries;
        rotate(rot);
        log(logType::INFO, "tile loaded with name " + fileName + " with rotation " + std::to_string(int(rot)));
    }
    else log(logType::ERROR, "cant open file: " + fileName);
}

tileBoundaryType tile::getBoundary(relativePosition rel) {
    switch (rel)
    {
    case right:
        return boundaries[0];
        break;
    case up:
        return boundaries[1];
        break;
    case left:
        return boundaries[2];
        break;
    case down:
        return boundaries[3];
        break;
    default:
        break;
    }
    log(logType::ERROR,"bad position");
    return tileBoundaryType::clear;
}

bool tile::isaFirstEnter() { return !wasEnteredBefore; }
void tile::changeWasEnteredBeforeStatus() { wasEnteredBefore = true; }

bool tile::isOccupiedByMonsters() {
    if (monstersOnTile.size() == 0)return false;
    else return true;
}
void  tile::addMonster(monster Monster) {
    monstersOnTile.push_back(Monster);
}


void tile::resolveInspection() {};
tile::~tile() {};
//############################################

bool foundableObject::canBeInspected() { return !wasInspected; }
//char foundableObject::objectSymbol() { return symbol; }
//################################

corridor::corridor(int id, tileType tT):tile(id,tT) {
    wasInspected = true;
}
void corridor::resolveInspection() { std::cout << "inspecting corridor" << std::endl; };

emptyRoom::emptyRoom(int id, tileType tT) :tile(id, tT) {
    wasInspected = true;
}
void emptyRoom::resolveInspection() { std::cout << "inspecting emptyRoom" << std::endl; };

fountain::fountain(int id, tileType tT) :tile(id, tT) {
    wasInspected = true;
}
void fountain::resolveInspection() { std::cout << "inspecting fountain" << std::endl; };

