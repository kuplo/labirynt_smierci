# pragma once

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "ITerminalDrawer.h"
#include "MapDrawer.h"

class TerminalGUI : public reportableObject {
public:

	TerminalGUI();
	~TerminalGUI();
	void setDrawer(std::unique_ptr<ITerminalDrawer>);

	void addInfo(const std::string& info, bool bForceUpdate);

	void refreshScreen();

	void startRendering();
	void stopRendering();

	char getCharInput();
private:

	void refreshScreen_();
	void renderScreenInfo_();

	bool m_bIsShuttingDown;
	std::unique_ptr<ITerminalDrawer> m_pITerminalDrawer;
	std::list<std::string> m_currentInfo;

	std::mutex m_mutex;
	std::condition_variable m_cv;
	bool m_bAllowDraw;
	std::unique_ptr<std::thread> m_pThread;

	std::optional<char> m_inputBuffer;
};
