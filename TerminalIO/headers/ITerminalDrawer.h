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

    static const int cBoardSize = 40;
protected:
	friend class TerminalGUI;
	char terminalCharBoard[cBoardSize][cBoardSize];
};
