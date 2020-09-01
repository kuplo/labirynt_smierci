#pragma once

#include "../../headers/reportableObject.h"

class TerminalGUI;

class ITerminalDrawer : public reportableObject
{
public:
    ITerminalDrawer();
    virtual ~ITerminalDrawer();
    void ClearBoard();

    virtual void FillTerminalCharBoard() = 0;

protected:
	friend class TerminalGUI;
	static const int cBoardSize = 40;
	char terminalCharBoard[cBoardSize][cBoardSize];
};
