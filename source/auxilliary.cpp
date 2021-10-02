#include "./../headers/auxilliary.h"
void rotateTileBoundaryTypeArray(std::array<tileBoundaryType, 4>& boundaries) {
    std::swap(boundaries[3], boundaries[0]);
    std::swap(boundaries[3], boundaries[1]);
    std::swap(boundaries[3], boundaries[2]);
}

unsigned dice6(int nextResult) { 
    static std::queue<unsigned> plannedResults;
    
    if (nextResult < 0) {
        if (plannedResults.size() == 0)return rand() % 6 + 1;
        else {
            unsigned returned = plannedResults.front();
            plannedResults.pop();
            return returned;
        }
    }
    plannedResults.push(nextResult);
    return 0;
}
unsigned dice3(int nextResult) {
    static std::queue<unsigned> plannedResults;

    if (nextResult < 0) {
        if (plannedResults.size() == 0)return rand() % 3 + 1;
        else {
            unsigned returned = plannedResults.front();
            plannedResults.pop();
            return returned;
        }
    }
    plannedResults.push(nextResult);
    return 0;
}

namespace Aux
{
    char Convert_(tileBoundaryType tbT)
    {
        switch (tbT)
        {
        case tileBoundaryType::corridor:
            return 'c';
        case tileBoundaryType::blocked:
            return 'b';
        case tileBoundaryType::passage:
            return 'p';
        default:
            return 'n';
        }
    }
}