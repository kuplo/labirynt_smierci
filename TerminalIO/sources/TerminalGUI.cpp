#include "../headers/TerminalGUI.h"

TerminalGUI::TerminalGUI() : m_bIsDrawerPresent(false){}

void TerminalGUI::setDrawer(std::unique_ptr<ITerminalDrawer> pTerminalDrawer)
{
	m_pITerminalDrawer = std::move(pTerminalDrawer);
	m_bIsDrawerPresent = true;
}

void TerminalGUI::refreshScreen()
{
	if (m_bIsDrawerPresent)
	{
		m_pITerminalDrawer->ClearBoard();
		m_pITerminalDrawer->FillTerminalCharBoard();
		refreshScreen_();
	}
}

void TerminalGUI::refreshScreen_()
{
	auto charBoard = m_pITerminalDrawer->terminalCharBoard;

	std::cout << std::endl;
	for (int x = 39 ; x >= 0 ; x--)
	{
		//Upper border
		if (x == 39)
		{
			std::cout << " ";
			for (int y = 0 ; y <= 40; y++) std::cout << "_ ";
			std::cout << std::endl;
		}

		for (int y = 0 ; y < 40; y++)
		{
			//Left border
			if (y == 0)std::cout << "| ";

			std::cout << charBoard[y][x] << ' ';

			//right border
			if (y == 39)std::cout << "| ";
		}
		std::cout << std::endl;

		//Down border
		if (x == 0)
		{
			std::cout << " ";
			for (int y = 0 ; y <= 40; y++) std::cout << "_ ";
			std::cout << std::endl;
		}
	}
}
