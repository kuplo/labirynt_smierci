#pragma once
#include <iostream>
#include "mapDrawer.h"
//#include <pair>
typedef std::pair < std::pair<unsigned, unsigned>, std::pair<unsigned, unsigned> > area;
class terminalGUI {
    std::reference_wrapper<mapDrawer> MapDrawer;
    char playArea[40][40];
    area boardArea;
    area infoArea;
public:
    terminalGUI(mapDrawer& mD);
    void draw(std::pair<int, int> teamPosition);
};
