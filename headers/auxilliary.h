#pragma once
#include <array>
enum tileRotation { x0, x1, x2,x3 };
enum tileBoundaryType {corridor,passage,blocked,clear};
enum relativePosition { right, up, left, down ,center};
enum moveActionResponse {addTile,simpleMove,notAllowed};
void rotateTileBoundaryTypeArray(std::array<tileBoundaryType, 4>& boundaries);
class test_class;

