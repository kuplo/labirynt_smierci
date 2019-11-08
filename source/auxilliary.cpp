#include "./../headers/auxilliary.h"
void rotateTileBoundaryTypeArray(std::array<tileBoundaryType, 4>& boundaries) {
    std::swap(boundaries[3], boundaries[0]);
    std::swap(boundaries[3], boundaries[1]);
    std::swap(boundaries[3], boundaries[2]);
}

