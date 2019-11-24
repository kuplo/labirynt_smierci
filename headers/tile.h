#pragma once
#include "reportableObject.h"
#include<fstream>
#include<list>
#include"mapDrawer.h"
#include"auxilliary.h"
#include"monster.h"
#include <array>
extern std::string tileFolder;
class mapDrawer;


class tile;

class foundableObject : public reportableObject {
protected:
    bool wasInspected;
 //   char symbol;
public:
 //   foundableObject(bool )
    virtual void resolveInspection() = 0;
    bool canBeInspected();
 //   char objectSymbol();
};


class tile : public reportableObject {
    friend class mapDrawer;
    int id;
    char shape[5][5];
    std::array<tileBoundaryType,4> boundaries;
    void rotate90degrees();
    tileType TileType;
    std::list<monster> monstersOnTile;
    bool wasEnteredBefore = false;
public:
    tile(int id,tileType tT);
    void loadTile(const std::string& fileName, std::array<tileBoundaryType, 4> preRotationBoundaries,tileRotation rot);
    void rotate(tileRotation rot);
    int&& getId();
    tileType getTileType();
    tileBoundaryType getBoundary(relativePosition rel);

    bool isaFirstEnter();
    void changeWasEnteredBeforeStatus();

    bool isOccupiedByMonsters();
    void addMonster(monster Monster);

    virtual void resolveInspection();
    virtual ~tile();
};


class corridor : public foundableObject,public tile {
public:
    corridor(int id, tileType tT);
    virtual void resolveInspection();
};


class emptyRoom : public foundableObject, public tile {
public:
    emptyRoom(int id, tileType tT);
    virtual void resolveInspection();
};


class fountain: public foundableObject, public tile {
public:
    fountain(int id, tileType tT);
    virtual void resolveInspection();
};
