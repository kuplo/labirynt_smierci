#include "./../headers/tile.h"

tile::tile(int id) :id(id) {}

int&& tile::getId() { return std::move(id); }

void tile::rotate90degrees() {
    int N = 5;
    for (int i = 0; i < N / 2; i++) {
        for (int j = i; j < N - i - 1; j++) {
            char temp = shape[i][j];
            shape[i][j] = shape[N - 1 - j][i];
            shape[N - 1 - j][i] = shape[N - 1 - i][N - 1 - j];
            shape[N - 1 - i][N - 1 - j] = shape[j][N - 1 - i];
            shape[j][N - 1 - i] = temp;
        }
    }
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
}