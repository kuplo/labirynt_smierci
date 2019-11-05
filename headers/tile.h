#pragma once
#include "reportableObject.h"
#include<fstream>
#include<list>
#include"mapDrawer.h"
#include"rotation.h"
extern std::string tileFolder;
class mapDrawer;

class tile : public reportableObject {
    friend class mapDrawer;
    int id;
    char shape[5][5];
    void rotate90degrees();
    void rotate(tileRotation rot);
public:
    tile(int id);
    void loadtile(const std::string& fileName,tileRotation rot);
    int&& getId();
};