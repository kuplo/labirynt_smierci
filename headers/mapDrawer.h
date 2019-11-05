#pragma once
#include <iostream>
#include "board.h"
#include "tile.h"
#include "reportableObject.h"
#include <functional>
//template<typename T>
//class reference_wrapper
//{
//    T* ptr;
//
//public:
//    using type = T;
//
//    reference_wrapper(T& val) noexcept
//        : ptr(std::addressof(val))
//    {}
//
//    reference_wrapper(T&&) = delete;
//
//    T& get() const noexcept { return *ptr; }
//    operator T&() const noexcept { return *ptr; }
//
//    template<typename... Args>
//    auto operator()(Args&&... args)
//        -> std::result_of_t<T&(Args...)>
//    {
//        return std::invoke(*ptr, std::forward<Args>(args)...);
//    }
//};




class board;
class tile;

extern tile dummyTile;
class mapDrawer:public reportableObject {
    int mapSizeX;
    int mapSizeY;
    int minX, minY, maxX, maxY;
    char** charMap;
    std::reference_wrapper<const board> Board;
    void deleteMap();
    void reshapeMap();
    //void fillMapSingleTile(tile& Tile, unsigned startingX, unsigned startingY);
    void fillMap();
    void fillMapWithSingleTile(tile& Tile, unsigned startingX, unsigned startingY);
public:
    mapDrawer(const board& gameBoard);
    void drawMap();
    ~mapDrawer();
};