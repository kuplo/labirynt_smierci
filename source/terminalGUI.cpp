#include "./../headers/terminalGUI.h"
std::stringstream GUIstream;


terminalGUI::terminalGUI(mapDrawer& MapDrawer):MapDrawer(MapDrawer) {
    for (int i = 39; i >= 0; i--) {
        for (int j = 0; j < 40; j++) {
            playArea[i][j] = ' ';
            if (j == 0 || j == 39 || i == 0 || i == 39)playArea[i][j] = 'O';
        }
    }
}

void terminalGUI::draw(std::pair<int,int> teamPosition) {
  /*  for (int i = 40; i >= 0; i--) {
        std::cout << "\x1b[A";
    }*/

    for (int i = 39; i >= 0; i--) {
        for (int j = 0; j < 40; j++) {
            playArea[i][j] = ' ';
            if (j == 0 || j == 39 || i == 0 || i == 39 || j== 5)playArea[i][j] = 'O';
        }
    }

    MapDrawer.get().drawMap();
    unsigned totalMapX = MapDrawer.get().mapSizeX;
    unsigned totalMapY = MapDrawer.get().mapSizeY;
    //druzyna zawsze na pozycji 20 20
    teamPosition.first += abs(MapDrawer.get().minX) + 1;
    teamPosition.second += abs(MapDrawer.get().minY) + 1;
    std::pair<int, int> translate = { 20 - teamPosition.first,20 - teamPosition.second };
   
    for (int i = 0; i < totalMapX; i++) {
        for (int j = 0; j < totalMapY; j++) {
            int newi = i + translate.first;
            int newj = j + translate.second;
         //   std::cout << i + translate.first << ' ' <<j+ translate.second << std::endl;
            if ( (newi < 38 ) && (newi > 1 )&& (newj < 38) && (newj > 5) ) {
                playArea[newi][newj] = MapDrawer.get().charMap[i][j];
            }
        }
    }

 /*   std::string line;
    line = GUIstream.str();
    unsigned escapesInstring = 0;
    for (auto& ch : line) { if (ch == '\n')escapesInstring++; }

    for (auto[lineIterator, i] = std::pair(0, 4); i >= 1; i--) {
        if (escapesInstring < 1)break;
        for (unsigned j=2; j < 40; j++) {
            if (line[lineIterator] != '\n') {
                playArea[j][i] = line[lineIterator];
                lineIterator++;
            }
            else {
                lineIterator++;
                escapesInstring--;
                break;
            }
        }
    }*/

    for (int i = 39; i >= 0; i--) {
        for (int j = 0; j < 40; j++) {
            std::cout << playArea[j][i] << ' ';
        }
        std::cout << std::endl;
    }

 
   
}

