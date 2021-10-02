#include "../headers/TerminalGUI.h"
#include <curses.h>

namespace nc
{
	void endl(){printw("\n");}

	void line(const int n)
	{	
		std::string line("_ ");
		for(int i=0;i<n;i++)
		{
			printw(line.c_str());
		}
	};

}

TerminalGUI::TerminalGUI() : m_bIsShuttingDown(false) 
{
	initscr();
	cbreak(); 
	noecho();
}

TerminalGUI::~TerminalGUI() 
{
	m_bIsShuttingDown = true;
	m_cv.notify_one();
	m_pThread->join();

	endwin();
}

void TerminalGUI::setDrawer(std::unique_ptr<ITerminalDrawer> pTerminalDrawer)
{
	std::lock_guard lock(m_mutex);
	m_pITerminalDrawer = std::move(pTerminalDrawer);
}

void TerminalGUI::addInfo(const std::string& info, bool bForceUpdate)
{
	std::lock_guard lock(m_mutex);
	
	m_currentInfo.push_back(info);
	if(bForceUpdate)
	{
		m_bAllowDraw = true;
		m_cv.notify_one();
	}
}

void TerminalGUI::refreshScreen()
{
	if (!m_pITerminalDrawer)
	{
		log(reportableObject::ERROR, "Terminal Drawer required!");
		return;
	}
	std::lock_guard lock(m_mutex);

	m_bAllowDraw = true;
	m_cv.notify_one();
}

void TerminalGUI::refreshScreen_()
{
	clear();
	auto charBoard = m_pITerminalDrawer->terminalCharBoard;
	const int cBSize = m_pITerminalDrawer->cBoardSize;
	
	nc::endl();
	for (int x = cBSize - 1 ; x >= 0 ; x--)
	{
		//Upper border
		if (x == cBSize - 1)
		{
			nc::endl();
			printw("  ");
			nc::line(cBSize);
			nc::endl();
			continue;
		}

		for (int y = 0 ; y < cBSize; y++)
		{	
			std::string line;
			line.reserve(cBSize*2);
			line.push_back(charBoard[y][x]);
			line.push_back(' ');
			//Left border
			if (y == 0)line.push_back('|');
			//right border
			if (y == cBSize-1)line.push_back('|');
			printw(line.c_str());
		}
		nc::endl();

		//Down border
		if (x == 0)
		{
			printw("  ");
			nc::line(cBSize);
			nc::endl();
			continue;
		}
	}
	renderScreenInfo_();

	refresh();
}

void TerminalGUI::renderScreenInfo_()
{
	for (auto& msg : m_currentInfo)
	{
		printw(msg.c_str());
		nc::endl();
	}
	m_currentInfo.clear();
}

void TerminalGUI::startRendering()
{
	if (m_pThread)
	{
		log(reportableObject::ERROR, "Already rendering!");
		return;
	}

	std::lock_guard lock(m_mutex);

	m_pThread = std::make_unique<std::thread>([this]()
	{
		while(true)
		{
			std::unique_lock<std::mutex> lk(m_mutex);
			m_cv.wait(lk, [this]{return m_bAllowDraw || m_bIsShuttingDown;});

			if(m_bIsShuttingDown)
			{
				return;
			}

			m_pITerminalDrawer->ClearBoard();
			m_pITerminalDrawer->FillTerminalCharBoard();
			refreshScreen_();
			m_bAllowDraw = false;
		}
	});
}

char TerminalGUI::getCharInput()
{
	//no mutex needed

	if(m_inputBuffer)
	{
		char ch = *m_inputBuffer;
		m_inputBuffer.reset();
		return ch;
	}

	return getch();
}