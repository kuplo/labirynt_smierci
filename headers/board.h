#pragma once
#include<fstream>
#include<list>
#include<vector>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <array>
#include "reportableObject.h"
#include"tile.h"
#include"auxilliary.h"
class mapDrawer;
class tile;

typedef std::pair< std::reference_wrapper<tile>, std::vector<std::reference_wrapper<tile>> > tileAndNeigbours;



extern std::string tileFolder;
extern tile dummyTile;


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
    tile* startingTile;
 //   std::list<tileAndNeigbours> listOfTilesAndNeighbours;
    std::pair<int, int> currentTeamPosition;
    //std::unordered_map<std::pair<int, int>, std::reference_wrapper<tile>> tileMapping;
    
    //[[deprecated]]
    //void linkTwoTiles(int id1, relativePosition position1, int id2, relativePosition position2);

    void addTile(const std::string& fileName);

public:
    std::unordered_map<std::pair<int, int>, std::reference_wrapper<tile>> tileMapping; //TODO do zmiany

    board();
    ~board();
    void addTile(tile& Tile, relativePosition rpos);
    void changePositionOfParty(relativePosition pos);
    std::pair<int, int> getCurrentTeamPosition();
    moveActionResponse moveActionRequest(relativePosition pos);
    std::array<tileBoundaryType, 4> getBoundariesOfNeighbourTile(relativePosition rpos);
    tile& getCurrentTile();
};
