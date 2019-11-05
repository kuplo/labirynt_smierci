#pragma once
#include<fstream>
#include<list>
#include<vector>
#include <functional>
#include <iterator>
#include <unordered_map>
#include "reportableObject.h"
#include"tile.h"
#include"rotation.h"
class mapDrawer;
class tile;

typedef std::pair< tile*, std::vector<std::reference_wrapper<tile>> > tileAndNeigbours;



extern std::string tileFolder;
extern tile dummyTile;
enum relativePosition{right,up,left,down};

template<> struct std::hash<std::pair<int, int>> {  
    std::size_t operator()(const std::pair<int, int>& k) const {
        std::hash<int> h;
        return h(k.first+10000)*10000 + h(k.second+10000);
    }
};
template<>
struct std::equal_to<std::pair<int, int>> {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return  ( lhs.first==rhs.first ) && ( lhs.second == rhs.second );
    }
};



class board :public reportableObject {
    friend class mapDrawer;
    static unsigned numberOfTiles;
    std::list<tileAndNeigbours> listOfTilesAndNeighbours;
    std::pair<int, int> currentTeamPosition;
    std::unordered_map<std::pair<int, int>, std::reference_wrapper<tile>> tileMapping;
    
    void linkTwoTiles(int id1, relativePosition position1, int id2, relativePosition position2);
    void addTile(const std::string& fileName);
public:
    board();
    void addTile(const std::string& fileName, relativePosition relativePosition, tileRotation rot);
    ~board();
    void changePositionOfParty(relativePosition pos);
};
