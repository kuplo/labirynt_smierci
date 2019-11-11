#pragma once
#include <array>
#include <iostream>
#include <sstream> 
#include <random>
enum tileRotation { x0, x1, x2,x3 };
enum class tileBoundaryType {corridor,passage,blocked,clear};
enum relativePosition { right, up, left, down ,center};
enum moveActionResponse {addTile,simpleMove,notAllowed};
enum class tileType {none,entrance,corridor,emptyRoom,fountain,figure,trapDoor,mirror,furniture,altar,art,stairs};
//enum class GUIstate {};
void rotateTileBoundaryTypeArray(std::array<tileBoundaryType, 4>& boundaries);
extern std::stringstream GUIstream;
//class test_class;
unsigned dice6();
unsigned dice3();

