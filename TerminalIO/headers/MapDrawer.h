#pragma once

#include "ITerminalDrawer.h"
#include "../../headers/board.h"

class MapDrawer : public ITerminalDrawer
{
private:
	board& m_rBoard;

	void AddTile_(tile& Tile, unsigned startingX, unsigned startingY);
public:
	MapDrawer(board& rBoard);
	~MapDrawer();

    virtual void FillTerminalCharBoard() override;
};
