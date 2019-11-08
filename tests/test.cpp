#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include "./../headers/auxilliary.h"
#include "./../headers/board.h"
#include "./../headers/mapDrawer.h"
#include "./../headers/reportableObject.h"
#include "./../headers/tile.h"
#include "./../headers/tilePoolManager.h"

std::string tileFolder = "./../tiles/";
tile dummyTile(-1);

bool testBoundaries(tile& Tile, std::array<tileBoundaryType, 4> Boundaries) {
    std::array<tileBoundaryType, 4> tileBoundaries;
    for (int i = 0; i < 4; i++) {
        tileBoundaries[i] = Tile.getBoundary(static_cast<relativePosition>(i));
    }
    return tileBoundaries == Boundaries;
}
bool checkBoundariesOfCurrentTile(board& Board, std::array<tileBoundaryType, 4> expectedBoundaries) {
    std::array<tileBoundaryType, 4> b1 = Board.getBoundariesOfNeighbourTile(relativePosition::right);
    std::array<tileBoundaryType, 4> b2 = Board.getBoundariesOfNeighbourTile(relativePosition::up);
    std::array<tileBoundaryType, 4> b3 = Board.getBoundariesOfNeighbourTile(relativePosition::left);
    std::array<tileBoundaryType, 4> b4 = Board.getBoundariesOfNeighbourTile(relativePosition::down);
    std::cout << b1[2] << ' ' << b2[3] << ' ' << b3[0] << ' ' << b4[1] << std::endl;
    std::array<tileBoundaryType, 4> currentTileBoundaries = {b1[2],b2[3],b3[0],b4[1]};
  //  std::array<tileBoundaryType, 4> expectedBoundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::blocked };
    return expectedBoundaries == currentTileBoundaries;
}

BOOST_AUTO_TEST_SUITE(tile_)
BOOST_AUTO_TEST_CASE(tile_id)
{
    tile testTile(100);
    BOOST_CHECK(testTile.getId() == 100);
}
BOOST_AUTO_TEST_CASE(tile_boundary_and_rotations) {
    tile testTile(100);
    std::array<tileBoundaryType, 4> Boundaries = { tileBoundaryType::blocked,tileBoundaryType::clear,tileBoundaryType::corridor,tileBoundaryType::passage };
    testTile.loadTile("empty", Boundaries, tileRotation::x0);
    BOOST_CHECK(testBoundaries(testTile,Boundaries));
    testTile.rotate(tileRotation::x1);
    Boundaries = { tileBoundaryType::passage,tileBoundaryType::blocked,tileBoundaryType::clear,tileBoundaryType::corridor };
    BOOST_CHECK(testBoundaries(testTile, Boundaries));
    testTile.rotate(tileRotation::x3);
    Boundaries = { tileBoundaryType::blocked,tileBoundaryType::clear,tileBoundaryType::corridor,tileBoundaryType::passage };
    BOOST_CHECK(testBoundaries(testTile, Boundaries));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(board_)
BOOST_AUTO_TEST_CASE(board_board) {
    board Board;
    std::array<tileBoundaryType, 4> neighbourBoundaries=Board.getBoundariesOfNeighbourTile(relativePosition::center);
  //  std::cout << entranceBoundaries[0] << ' ' << entranceBoundaries[1] << ' ' << entranceBoundaries[2] << ' ' << entranceBoundaries[3] << std::endl;
    std::array<tileBoundaryType, 4> boundaries = { tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear };
    BOOST_CHECK(neighbourBoundaries == boundaries);
    BOOST_CHECK( checkBoundariesOfCurrentTile(Board,
    { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::blocked }));
    BOOST_CHECK(Board.getCurrentTile().getId() == 0);
}
BOOST_AUTO_TEST_CASE(board_teamPosition) {
    board Board;
    
    BOOST_CHECK(Board.getCurrentTeamPosition().first == 0 && Board.getCurrentTeamPosition().second == 0);
    Board.changePositionOfParty(relativePosition::right);
    BOOST_CHECK(Board.getCurrentTeamPosition().first == 5 && Board.getCurrentTeamPosition().second == 0);
    Board.changePositionOfParty(relativePosition::up);
    BOOST_CHECK(Board.getCurrentTeamPosition().first == 5 && Board.getCurrentTeamPosition().second == 5);
    Board.changePositionOfParty(relativePosition::left);
    BOOST_CHECK(Board.getCurrentTeamPosition().first == 0 && Board.getCurrentTeamPosition().second == 5);
    Board.changePositionOfParty(relativePosition::down);
    BOOST_CHECK(Board.getCurrentTeamPosition().first == 0 && Board.getCurrentTeamPosition().second == 0);

}
BOOST_AUTO_TEST_CASE(board_addTile) {
    board Board;
    tile Tile(100);
    Tile.loadTile("corridor3", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor },tileRotation::x0);
    Board.addTile(Tile,relativePosition::up);
    std::array<tileBoundaryType, 4> neighbourBoundaries = Board.getBoundariesOfNeighbourTile(relativePosition::up);
    std::array<tileBoundaryType, 4> boundaries = { tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::corridor };
    BOOST_CHECK(neighbourBoundaries == boundaries);
    Board.changePositionOfParty(relativePosition::up);
    boundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor };
    BOOST_CHECK(checkBoundariesOfCurrentTile(Board, boundaries));
}
BOOST_AUTO_TEST_CASE(board_moveActionRequest) {
    board Board;
    auto action = Board.moveActionRequest(relativePosition::up);
    BOOST_CHECK(action == moveActionResponse::addTile);
    action = Board.moveActionRequest(relativePosition::right);
    BOOST_CHECK(action == moveActionResponse::notAllowed);
    tile Tile(100);
    Tile.loadTile("corridor3", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor }, tileRotation::x0);
    Board.addTile(Tile, relativePosition::up);
    Board.changePositionOfParty(relativePosition::up);
    action = Board.moveActionRequest(relativePosition::down);
    BOOST_CHECK(action == moveActionResponse::simpleMove);
}


BOOST_AUTO_TEST_SUITE_END()

