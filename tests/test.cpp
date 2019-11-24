#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <boost/test/unit_test.hpp>
#include "./../headers/auxilliary.h"
#include "./../headers/board.h"
#include "./../headers/mapDrawer.h"
#include "./../headers/reportableObject.h"
#include "./../headers/tile.h"
#include "./../headers/tilePoolManager.h"
#include "./../headers/playableCharacter.h"
#include "./../headers/trapResolver.h"
#include "./../headers/monster.h"
#include "./../headers/monsterEncounter.h"
std::string tileFolder = "./../tiles/";
tile dummyTile(-1, tileType::none);

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
  //  std::cout << b1[2] << ' ' << b2[3] << ' ' << b3[0] << ' ' << b4[1] << std::endl;
    std::array<tileBoundaryType, 4> currentTileBoundaries = {b1[2],b2[3],b3[0],b4[1]};
  //  std::array<tileBoundaryType, 4> expectedBoundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::blocked };
    return expectedBoundaries == currentTileBoundaries;
}
void simulateCin(std::string text) {
    static std::istringstream input;
    input.str(text);
    std::streambuf* orig = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());
}


BOOST_AUTO_TEST_SUITE(tile_)
BOOST_AUTO_TEST_CASE(tile_id)
{
    tile testTile(100,tileType::none);
    BOOST_CHECK(testTile.getId() == 100);
}
BOOST_AUTO_TEST_CASE(tile_boundary_and_rotations) {
    tile testTile(100, tileType::none);
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
    tile Tile(100, tileType::corridor);
    Tile.loadTile("c_bcpc", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor },tileRotation::x0);
    Board.addTile(Tile,relativePosition::up);
    std::array<tileBoundaryType, 4> neighbourBoundaries = Board.getBoundariesOfNeighbourTile(relativePosition::up);
    std::array<tileBoundaryType, 4> boundaries = { tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::corridor };
    BOOST_CHECK(neighbourBoundaries == boundaries);
    Board.changePositionOfParty(relativePosition::up);
    boundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor };
    BOOST_CHECK(checkBoundariesOfCurrentTile(Board, boundaries));
}
BOOST_AUTO_TEST_CASE(board_currentTile) {
    board Board;
    tile Tile(100, tileType::corridor);
    Tile.loadTile("c_bcpc", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor }, tileRotation::x0);
    Board.addTile(Tile, relativePosition::up);
    Board.changePositionOfParty(relativePosition::up);
    tile Tile2(101, tileType::corridor);
    Tile2.loadTile("c_bcpc", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor }, tileRotation::x2);
    Board.addTile(Tile2, relativePosition::left);
    Board.changePositionOfParty(relativePosition::left);
    BOOST_CHECK(Tile2.getId() == Board.getCurrentTile().getId());
}

BOOST_AUTO_TEST_CASE(board_moveActionRequest) {
    board Board;
    auto action = Board.moveActionRequest(relativePosition::up);
    BOOST_CHECK(action == moveActionResponse::addTile);
    action = Board.moveActionRequest(relativePosition::right);
    BOOST_CHECK(action == moveActionResponse::notAllowed);
    tile Tile(100, tileType::corridor);
    Tile.loadTile("c_bcpc", { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::passage,tileBoundaryType::corridor }, tileRotation::x0);
    Board.addTile(Tile, relativePosition::up);
    Board.changePositionOfParty(relativePosition::up);
    action = Board.moveActionRequest(relativePosition::down);
    BOOST_CHECK(action == moveActionResponse::simpleMove);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(tilePoolManager_)
BOOST_AUTO_TEST_CASE(tilePoolManager_boundaries) {
    tilePoolManager TP;
    std::array<tileBoundaryType, 4> boundaries = { tileBoundaryType::blocked,tileBoundaryType::corridor,tileBoundaryType::blocked,tileBoundaryType::corridor };
    simulateCin("2");
    auto tile =TP.getNewTile(boundaries);
   
    BOOST_CHECK(testBoundaries(tile, boundaries));
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(playableCharacter_)
BOOST_AUTO_TEST_CASE(playableCharacter_miscellaneous) {
    playableCharacter pl;
    pl.strength = 3;
    pl.assignDamage(1);
    BOOST_CHECK(pl.strength == 2);
    BOOST_CHECK(!pl.isAffectedBy(characterModifiers::death));
    pl.assignDamage(2);
    BOOST_CHECK(pl.isAffectedBy(characterModifiers::death));
    pl.abilities[characterAbilities::darkGate] = 2;
    BOOST_CHECK(pl.haveAbility(characterAbilities::darkGate));
    BOOST_CHECK(pl.getAbilityLevel(characterAbilities::darkGate)==2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(dice_test)
BOOST_AUTO_TEST_CASE(dice_Correctness) {
    dice6(1);
    dice6(4);
    dice6(6);
    BOOST_CHECK(1 == dice6());
    BOOST_CHECK(4 == dice6());
    dice6(5);
    BOOST_CHECK(6 == dice6());
    BOOST_CHECK(5 == dice6());
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(trapResolver_)
BOOST_AUTO_TEST_CASE(trapResolver_check) {
    playableCharacter pl;
    pl.strength = 3;
    pl.abilities[characterAbilities::trapDismantle] = 2;
    playableCharacter pl2;
    pl2.strength = 3;
    std::vector<playableCharacter> team;
    team.push_back(pl);
    team.push_back(pl2);
    dice6(1);
    simulateCin("0");
    dice6(1);
    dice6(5);
    trapResolver::resolvePassageTrap(team[1],team);
    BOOST_CHECK(team[0].strength == 3);
    dice6();

    dice6(1);
    dice6(5);
    dice6(4);
    dice3(6);
    simulateCin("0");
    trapResolver::resolvePassageTrap(team[1], team);
    BOOST_CHECK(team[0].strength == 2 && team[1].strength == 2);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(monsterEncounter_)
BOOST_AUTO_TEST_CASE(monsterEncounter_corridor) {
    tilePoolManager tpManager;
    std::array<tileBoundaryType, 4> Boundaries = { tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear };
    tile* corridorTile;
    while (true) {
        simulateCin("0");
        corridorTile = &tpManager.getNewTile(Boundaries);
        if (corridorTile->getTileType() == tileType::corridor) { break; }
    }
    dice6(2);
    monsterEncounter::resolveMonsterEncounter(*corridorTile);
    BOOST_CHECK(!corridorTile->isOccupiedByMonsters());
    dice6(1);
    monsterEncounter::resolveMonsterEncounter(*corridorTile);
    BOOST_CHECK(corridorTile->isOccupiedByMonsters());
    
}
BOOST_AUTO_TEST_CASE(monsterEncounter_room) {
    tilePoolManager tpManager;
    std::array<tileBoundaryType, 4> Boundaries = { tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear,tileBoundaryType::clear };
    tile* roomTile;
    while (true) {
        simulateCin("0");
        roomTile = &tpManager.getNewTile(Boundaries);
        if (roomTile->getTileType() != tileType::corridor) { break; }
    }
    dice6(2);
    monsterEncounter::resolveMonsterEncounter(*roomTile);
    BOOST_CHECK(roomTile->isOccupiedByMonsters());

    while (true) {
        simulateCin("0");
        roomTile = &tpManager.getNewTile(Boundaries);
        if (roomTile->getTileType() != tileType::corridor) { break; }
    }
    dice6(5);
    monsterEncounter::resolveMonsterEncounter(*roomTile);
    BOOST_CHECK(!roomTile->isOccupiedByMonsters());
    dice6(2);
    monsterEncounter::resolveMonsterEncounter(*roomTile);
    BOOST_CHECK(!roomTile->isOccupiedByMonsters());
    dice6(1);
    monsterEncounter::resolveMonsterEncounter(*roomTile);
    BOOST_CHECK(roomTile->isOccupiedByMonsters());
}
BOOST_AUTO_TEST_SUITE_END()