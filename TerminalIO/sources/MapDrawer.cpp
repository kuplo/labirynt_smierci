#include "../headers/MapDrawer.h"

MapDrawer::MapDrawer(board& rBoard) : ITerminalDrawer(), m_rBoard{rBoard} {}

MapDrawer::~MapDrawer(){}

void MapDrawer::FillTerminalCharBoard()
{
	std::pair<int, int> currentTeamPos = m_rBoard.getCurrentTeamPosition();

	auto RelativeToAbsolutePos = [&currentTeamPos](const std::pair<int, int>& relPos){
		return std::make_pair(currentTeamPos.first + relPos.first, currentTeamPos.second + relPos.second);};

	auto& tileMapping = m_rBoard.tileMapping;
	for (int tileRelPosX = -cBoardSize/2; tileRelPosX< cBoardSize/2; tileRelPosX = tileRelPosX+5 )
	{
		for (int tileRelPosY = -cBoardSize/2; tileRelPosY< cBoardSize/2; tileRelPosY = tileRelPosY+5 )
		{
			auto tileToDraw = tileMapping.find(RelativeToAbsolutePos({tileRelPosX, tileRelPosY}));

			if (tileToDraw == tileMapping.end())
			{
				AddTile_(dummyTile,tileRelPosX + cBoardSize/2, tileRelPosY + cBoardSize/2);
			}
			else
			{
				AddTile_(tileToDraw->second.get(),tileRelPosX + cBoardSize/2, tileRelPosY + cBoardSize/2);
			}
		}
	}

	terminalCharBoard[cBoardSize/2 + 1][ cBoardSize/2 + 1]='T';
}

void MapDrawer::AddTile_(tile& Tile, unsigned startingX, unsigned startingY)
{		//FixMe: do not rotate the tile and then reverse it ...
		Tile.rotate(tileRotation::x3);
	    for (int i = 0; i < 5; i++) {
	        for (int j = 0; j < 5; j++) {
				
	        	terminalCharBoard[startingX + i][startingY + j] = Tile.shape[i][j];
	        }
	    }
		Tile.rotate(tileRotation::x1);
	    if (Tile.isOccupiedByMonsters())  terminalCharBoard[startingX + 3][startingY + 3] = 'M';
}
