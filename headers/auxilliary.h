#pragma once
#include <array>
#include <iostream>
#include <sstream> 
#include <random>
#include <queue>
enum tileRotation { x0, x1, x2,x3 };
enum class tileBoundaryType {corridor,passage,blocked,clear};
enum relativePosition { right, up, left, down ,center};
enum moveActionResponse {addTile,simpleMove,notAllowed};
enum class tileType {none,entrance,corridor,emptyRoom,fountain,figure,trapDoor,mirror,furniture,altar,art,stairs};
enum class dominantSuns {redSun,yellowSun,blueSun};

enum class weaponType { dagger, knife,bow, sword,hammer,axe, monster };

enum class turnPhase {init,move,passageTrap,monsterEncounter, battle,tileInspection,exit};

void rotateTileBoundaryTypeArray(std::array<tileBoundaryType, 4>& boundaries);
extern std::stringstream GUIstream;

unsigned dice6(int nextResult=-1);
unsigned dice3(int nextResult=-1);

namespace Aux
{
    char Convert_(tileBoundaryType tbT);
}