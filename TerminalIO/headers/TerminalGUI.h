# pragma once

#include <memory>

#include "ITerminalDrawer.h"
#include "MapDrawer.h"

class TerminalGUI {
public:

	TerminalGUI();

	void setDrawer(std::unique_ptr<ITerminalDrawer>);

	void refreshScreen();
private:

	void refreshScreen_();

	std::unique_ptr<ITerminalDrawer> m_pITerminalDrawer;

	bool m_bIsDrawerPresent;
};
