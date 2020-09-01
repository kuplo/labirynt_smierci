#include "../headers/ITerminalDrawer.h"

ITerminalDrawer::ITerminalDrawer(){ClearBoard();}

ITerminalDrawer::~ITerminalDrawer(){}

void ITerminalDrawer::ClearBoard()
{
	for (int i=0;i<cBoardSize;i++)
		for (int j=0;j<cBoardSize;j++)
			terminalCharBoard[i][j]=' ';
}
