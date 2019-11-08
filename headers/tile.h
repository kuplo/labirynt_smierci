#pragma once
#include "reportableObject.h"
#include<fstream>
#include<list>
#include"mapDrawer.h"
#include"auxilliary.h"
#include <array>
extern std::string tileFolder;
class mapDrawer;

class tile : public reportableObject {
    friend class mapDrawer;
    int id;
    char shape[5][5];
    std::array<tileBoundaryType,4> boundaries;
    void rotate90degrees();
public:
    tile(int id);
    void loadTile(const std::string& fileName, std::array<tileBoundaryType, 4> preRotationBoundaries,tileRotation rot);
    void rotate(tileRotation rot);
    int&& getId();
    tileBoundaryType getBoundary(relativePosition rel);
};